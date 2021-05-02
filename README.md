# cvtest
# Computer Vision Test
## Unit Test, Integration Test, System Test, Acceptance Test for Computer Vision and Deep Learning 

Do you want to test your output of computer vision application which is video or images? 


## Standard test for computer vision application 
There isn't any standard test for computer vision program. I wrote many test by myself and I would like to share some of them here. For example, I write a program to test docker and check the processing time, memory usage, CPU usage, etc. 
In computer vision application sometime you need to check the output which is the image. How do you want to check it. I write some program to check the output which is the image and compare the ground truth. I check some well known methods such as PSNR, SSIM, Image quality, distortion, brightness, sharpness, etc.
Furthermore, I check much different hardware and write some test for computer vision application base on different hardware architecture  and Evaluation hardware.

Do you want to know your program Automatically adjusting brightness of image in the right way?, How do you know using generic sharpening kernel to remove blurriness is working?, How to do check FPS process?, Which OCR system work better for your input image?


* Docker Test: testing computer vision application for different docker setup; how to optimize input/output for docker which use inputs such as images or videos; how to test for load balancing, number of pods, memory usage; CPU usage; Bandwidth ; how to compress data; how to encrypt/decrypt data for using in docker; check the connectivity issue; REST API, FAST API, JSON file checker; converting format; converting labeling format; check the version of library and packages; 
* profiling the performance of the pipeline; writing clean code for certification; software certification standards, e.g. ISO27001, DO160
* 
