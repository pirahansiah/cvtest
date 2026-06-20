# CVTest — Computer Vision Testing Framework

[![C++](https://img.shields.io/badge/C%2B%2B-17-blue?logo=cplusplus&logoColor=white)]()
[![Visual Studio](https://img.shields.io/badge/Visual%20Studio-2022-purple?logo=visualstudio&logoColor=white)]()
[![OpenCV](https://img.shields.io/badge/OpenCV-4.10-blue?logo=opencv&logoColor=white)](https://opencv.org/)
[![License](https://img.shields.io/badge/License-Apache%202.0-green.svg)](LICENSE)

Comprehensive testing framework for computer vision and deep learning applications — unit tests, integration tests, system tests, and acceptance tests.

## Overview

Standardized testing methodologies for CV applications where traditional software testing falls short. This project addresses the unique challenges of testing **image and video processing pipelines** where outputs are visual and correctness is subjective.

## Test Categories

| Test Type | Purpose | Tools |
|-----------|---------|-------|
| **Unit Tests** | Individual function correctness | Google Test, OpenCV assertions |
| **Integration Tests** | Pipeline stage interactions | Custom validators |
| **System Tests** | End-to-end application behavior | Docker, profiling |
| **Acceptance Tests** | Business requirement validation | Visual comparison metrics |

## Key Capabilities

### Image Quality Metrics

| Metric | Description | Use Case |
|--------|-------------|----------|
| **PSNR** | Peak Signal-to-Noise Ratio | Image reconstruction quality |
| **SSIM** | Structural Similarity Index | Perceptual quality comparison |
| **MSE** | Mean Squared Error | Pixel-level accuracy |
| **LPIPS** | Learned Perceptual Image Patch Similarity | Deep feature-based quality |
| **FID** | Fréchet Inception Distance | Generated image quality |
| **CLIP Score** | Text-image alignment | Generative model evaluation |

### Performance Profiling

- **Processing time** per frame / per pipeline stage
- **Memory usage** monitoring (peak, average, leak detection)
- **CPU/GPU utilization** tracking
- **FPS** measurement under load
- **Latency distribution** (P50, P95, P99)

### Docker Testing

- Containerized environment testing
- Input/output format validation
- Load balancing and pod scaling tests
- Bandwidth and compression benchmarks
- REST API / FastAPI endpoint validation

### Hardware Evaluation

- Multi-platform testing (CPU, GPU, edge devices)
- Comparison across hardware architectures
- Power consumption profiling
- Thermal throttling detection

## ImageProcessingClass

The `ImageProcessingClass` provides utility functions to extract information from each step of CV algorithms:

```cpp
#include "ImageProcessingClass.h"

// Get intermediate results from pipeline stages
ImageProcessingClass ipc;
auto featureMap = ipc.getIntermediateResult(stage_idx);
auto metrics = ipc.computeMetrics(groundTruth, output);
```

## 2025–2026: Modern CV Testing Tools

### Testing Frameworks

| Tool | Type | Key Feature |
|------|------|-------------|
| **Google Test** | Unit testing | C++ standard, mocking |
| **pytest** | Python testing | Fixture-based, parametrized |
| **FiftyOne** | Dataset evaluation | Visual model analysis |
| **TorchMetrics** | DL metrics | Standardized metric computation |
| **OpenCV DNN** | Inference testing | Cross-backend validation |

### CI/CD for CV

```yaml
# GitHub Actions example
- name: Run CV Tests
  run: |
    pytest tests/unit/ -v
    pytest tests/integration/ -v
    python tests/visual_regression.py --threshold 0.95
    docker-compose -f tests/docker-compose.test.yml up
```

### Visual Regression Testing (2025+)

| Method | Accuracy | Speed |
|--------|----------|-------|
| **Pixel-wise diff** | Low (brittle) | Fast |
| **SSIM comparison** | Medium | Fast |
| **LPIPS (perceptual)** | High | Medium |
| **CLIP-based evaluation** | High (semantic) | Slow |
| **Human preference score** | Gold standard | Manual |

### Recommended Stack

```bash
# Testing dependencies
pip install pytest fiftyone torchmetrics lpips
pip install ultralytics onnxruntime-gpu

# C++ testing
vcpkg install gtest opencv4
```

## Software Certification

| Standard | Domain |
|----------|--------|
| **ISO 27001** | Information security management |
| **DO-160** | Environmental conditions for airborne equipment |
| **ISO 26262** | Automotive functional safety |
| **IEC 62304** | Medical device software lifecycle |
| **ISO 9001** | Quality management systems |

## Project Structure

```
cvtest/
├── Book/
│   └── Chapter_01_01.cpp    # Chapter code examples
├── cvtest/
│   ├── ImageProcessingClass.cpp
│   ├── ImageProcessingClass.h
│   ├── cvtest.sln
│   └── cvtest.vcxproj
├── LICENSE
└── README.md
```

## Requirements

- Visual Studio 2022 (v143 toolset)
- OpenCV 4.10+
- Google Test (via vcpkg)
- CMake 3.20+

## References

- [OpenCV Testing Module](https://github.com/opencv/opencv/tree/4.x/modules/ts)
- [Google Test Primer](https://google.github.io/googletest/primer.html)
- [FiftyOne Model Evaluation](https://docs.voxel51.com/)
- [TorchMetrics](https://torchmetrics.readthedocs.io/)

## Author

**Farshid Pirahansiah**
- Website: [pirahansiah.com](https://www.pirahansiah.com)
- GitHub: [github.com/pirahansiah](https://github.com/pirahansiah)
- LinkedIn: [linkedin.com/in/pirahansiah](https://www.linkedin.com/in/pirahansiah)

## License

Apache License 2.0 — See [LICENSE](LICENSE) for details.
