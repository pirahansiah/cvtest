FROM ubuntu:24.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    libopencv-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY CMakeLists.txt .
COPY cvtest/ cvtest/
COPY Book/ Book/
COPY tests/ tests/

RUN cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON && \
    cmake --build build --parallel $(nproc)

FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    libopencv-core406t64 \
    libopencv-highgui406t64 \
    libopencv-imgproc406t64 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY --from=builder /build/build/cvtest /app/cvtest
COPY --from=builder /build/build/tests/test_histogram /app/test_histogram
COPY --from=builder /build/build/tests/test_image_processing /app/test_image_processing

ENTRYPOINT ["/app/cvtest"]
