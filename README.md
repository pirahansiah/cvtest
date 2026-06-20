# CVTest — Computer Vision Testing Framework

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue?logo=cplusplus&logoColor=white)]()
[![CMake](https://img.shields.io/badge/CMake-3.20+-064F8C?logo=cmake&logoColor=white)]()
[![OpenCV](https://img.shields.io/badge/OpenCV-5.x-5C3EE8?logo=opencv&logoColor=white)](https://opencv.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

Computer vision image processing utilities with histogram computation, unit tests, and CMake cross-platform build.

## Project Structure

```
cvtest/
├── cvtest/
│   ├── ImageProcessingClass.cpp   # Core image processing functions
│   ├── ImageProcessingClass.h     # Public API header
│   ├── cvtest.sln                 # Visual Studio solution
│   └── cvtest.vcxproj             # VS project file
├── Book/
│   └── Chapter_01_01.cpp          # Book chapter examples
├── tests/
│   ├── CMakeLists.txt             # Google Test configuration
│   ├── test_histogram.cpp         # Histogram unit tests
│   └── test_image_processing.cpp  # Image info unit tests
├── CMakeLists.txt                 # Top-level CMake build
├── Dockerfile                     # Multi-stage Docker build
├── README.md
└── LICENSE
```

## Build

### CMake (Linux/macOS)

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/cvtest Image/test_image.jpg
```

### Visual Studio 2022

Open `cvtest/cvtest.sln` and build with v143 toolset.

## Testing

```bash
cmake -B build -DBUILD_TESTS=ON
cmake --build build --parallel
cd build && ctest --output-on-failure
```

### Google Test

Tests cover:
- **Histogram functions**: color/gray histogram computation, output dimensions, edge cases (empty images, uniform images)
- **Image processing**: BGR and grayscale processing, error handling

## Docker

```bash
docker build -t cvtest .
docker run --rm -v $(pwd)/cvtest:/data cvtest /data/a.png
```

## Bug Fixes (v2.0)

- **Fixed off-by-one**: `histogram_gray()` now initializes all 256 bins (was `< 255`)
- **Fixed API misuse**: `Chapter_01_01.cpp` now uses `cv::cvtColor` instead of `convertTo` with wrong constant
- **Added const correctness**: All function parameters use `const cv::Mat&`
- **Cross-platform paths**: Removed hardcoded Windows paths, use `argv[1]` or defaults
- **Removed broken files**: Deleted `test2.cpp` (incomplete `cout<<` statement)
- **Namespace**: Functions wrapped in `cvtest::` namespace

## 12-Month Roadmap

| Phase | Timeline | Milestone |
|-------|----------|-----------|
| **Phase 1** | Month 1-2 | Comprehensive unit tests, cross-platform CMake, CI/CD pipeline |
| **Phase 2** | Month 3-4 | Image filtering pipeline (blur, sharpen, edge detection, morphology) |
| **Phase 3** | Month 5-6 | Video processing support with FFmpeg integration |
| **Phase 4** | Month 7-8 | ONNX Runtime integration for ML model inference |
| **Phase 5** | Month 9-10 | Performance benchmarking suite, SIMD/NEON optimization |
| **Phase 6** | Month 11-12 | Multi-platform CI (Linux, Windows, macOS), Docker registry, docs |

## Requirements

- CMake 3.20+
- C++17 compiler (GCC 12+, Clang 15+, MSVC v143)
- OpenCV 5.x
- Google Test (fetched automatically by CMake)

## References

- [OpenCV Documentation](https://docs.opencv.org/)
- [Google Test Primer](https://google.github.io/googletest/primer.html)
- [CMake Documentation](https://cmake.org/cmake/help/latest/)

## Author

**Dr. Farshid Pirahansiah** — [LinkedIn](https://linkedin.com/in/pirahansiah) | [GitHub](https://github.com/pirahansiah)

## License

MIT License — See [LICENSE](LICENSE) for details.
