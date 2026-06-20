# ROADMAP.md — CVTest Framework

## 12-Month Vision (Jul 2025 – Jun 2026)

Transform CVTest into a production-grade C++ computer vision testing framework with comprehensive image processing utilities, performance benchmarking, and cross-platform CI/CD — serving as the standard testing infrastructure for OpenCV-based projects.

### Q1 (Jul–Sep 2025): Foundation

- [ ] Complete C++17 migration with structured bindings and std::optional
- [ ] Achieve >90% Google Test coverage with CI/CD pipeline
- [ ] Add CMake presets for Linux, macOS, and Windows
- [ ] Standardize on modern C++ patterns (RAII, smart pointers)

### Q2 (Oct–Dec 2025): Image Processing

- [ ] Add image filtering pipeline (blur, sharpen, edge detection, morphology)
- [ ] Implement color space conversion utilities (BGR, HSV, LAB)
- [ ] Create image comparison and similarity metrics
- [ ] Add batch processing support for directory-based operations

### Q3 (Jan–Mar 2026): Performance & ML

- [ ] Performance benchmarking suite with Google Benchmark
- [ ] ONNX Runtime integration for ML model inference testing
- [ ] SIMD/NEON optimization for histogram computation
- [ ] Video processing support with FFmpeg integration

### Q4 (Apr–Jun 2026): Release

- [ ] Multi-platform CI (Linux, macOS, Windows) with automated testing
- [ ] Docker registry with versioned images
- [ ] v1.0 release with comprehensive documentation
- [ ] Community contribution guidelines and plugin architecture

## Technical Debt

- [ ] Remove hardcoded default paths from main function
- [ ] Consolidate duplicate histogram functions
- [ ] Replace raw pointers with smart pointers where applicable
- [ ] Add missing const qualifiers on member functions
- [ ] Fix inconsistent error handling (return codes vs exceptions)
- [ ] Remove deprecated OpenCV API calls
- [ ] Add compiler warning flags (-Wall, -Wextra, -Wpedantic)
- [ ] Standardize on CMake presets instead of manual configuration

## Future Features

- [ ] Real-time video analysis with GStreamer integration
- [ ] GPU-accelerated processing with CUDA kernels
- [ ] Multi-threaded batch processing for large image sets
- [ ] Image annotation and visualization tools
- [ ] Integration with Python bindings (pybind11)
- [ ] Support for new image formats (HEIF, AVIF)
- [ ] Automated regression testing for CV algorithms
- [ ] Performance profiling and optimization recommendations
