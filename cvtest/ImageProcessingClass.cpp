#include "ImageProcessingClass.h"

// Farshid Pirahansiah
// Optimization computer vision with deep learning in IoT device for real time purpose
// March 2022 

// ! this is a very critical comment
// * this is a highlighted comment
// TODO:  this is a TODO comment
// ? this is a question comment
// I use /*output*/ infront of each output variable to show input/output correctly

#include <iostream>
#include <cstdio>
#include <string>
#include <typeinfo>
#include <new>
#include <math.h> //round 
//  Install-Package opencv_450 -Version 4.5.0.202107263
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/ocl.hpp>


int histogram_color(cv::Mat src, cv::Mat &dst /*output*/)
{
    std::vector<cv::Mat> bgr_planes;
    split(src, bgr_planes);
    int histSize = 256;
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    bool uniform = true, accumulate = false;
    cv::Mat b_hist, g_hist, r_hist;
    calcHist(&bgr_planes[0], 1, 0, cv::Mat(), b_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, cv::Mat(), g_hist, 1, &histSize, histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, cv::Mat(), r_hist, 1, &histSize, histRange, uniform, accumulate);
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    cv::Mat histImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
    normalize(b_hist, b_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(g_hist, g_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    normalize(r_hist, r_hist, 0, histImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
    for (int i = 1; i < histSize; i++)
    {
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
            cv::Scalar(255, 0, 0), 2, 8, 0);
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
            cv::Scalar(0, 255, 0), 2, 8, 0);
        line(histImage, cv::Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
            cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
            cv::Scalar(0, 0, 255), 2, 8, 0);
    }
    dst= histImage;
    return 0;
}

int histogram_gray(cv::Mat image, cv::Mat &out /*output*/)
{
    // allcoate memory for no of pixels for each intensity value
    int histogram[256];

    // initialize all intensity values to 0
    for (int i = 0; i < 255; i++)
    {
        histogram[i] = 0;
    }

    // calculate the no of pixels for each intensity values
    for (int y = 0; y < image.rows; y++)
        for (int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y, x)]++;

    /*for (int i = 0; i < 256; i++)
        cout << histogram[i] << " ";*/

        // draw the histograms
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound((double)hist_w / 256);

    cv::Mat histImage(hist_h, hist_w, CV_8UC1, cv::Scalar(255, 255, 255));

    // find the maximum intensity element from histogram
    int max = histogram[0];
    for (int i = 1; i < 256; i++) {
        if (max < histogram[i]) {
            max = histogram[i];
        }
    }

    // normalize the histogram between 0 and histImage.rows

    for (int i = 0; i < 255; i++) {
        histogram[i] = ((double)histogram[i] / max) * histImage.rows;
    }


    // draw the intensity line for histogram
    for (int i = 0; i < 255; i++)
    {
        line(histImage, cv::Point(bin_w * (i), hist_h),
            cv::Point(bin_w * (i), hist_h - histogram[i]),
            cv::Scalar(0, 0, 0), 1, 8, 0);
    }

    out = histImage;
    return 0;
}

int func_image_info(cv::Mat src, cv::Mat &dst /*output*/)
{
    try
    {
        printf("Image info ... \n");
        //start: image type 
        int type = src.type();
        std::string r;
        uchar depth = type & CV_MAT_DEPTH_MASK;
        uchar chans = 1 + (type >> CV_CN_SHIFT);
        switch (depth) {
        case CV_8U:  r = "8U"; break;
        case CV_8S:  r = "8S"; break;
        case CV_16U: r = "16U"; break;
        case CV_16S: r = "16S"; break;
        case CV_32S: r = "32S"; break;
        case CV_32F: r = "32F"; break;
        case CV_64F: r = "64F"; break;
        default:     r = "User"; break;
        }
        r += "C";
        r += (chans + '0');
        printf("\t the image type is = %s \n", r.c_str());
        //end: image type     cv::Size s = src.size();         int height = s.height;//rows          int width = s.width;//cols 
        int rows = src.rows;
        int cols = src.cols;
        printf("\t the image rows or height = %d and cols or width = %d\n", rows, cols);        
	if (src.channels()==3)
	{		
	    std::cout<<"Image is Color \n";
	}
	else
	{
	    std::cout<<"Image is Grayscale \n";
	}
	    
        //src.convertTo(src, CV_64F);
        //cv::cvtColor(src, src, cv::COLOR_GRAY2RGB);
        cv::Mat hist;
        if (type < 2)
        {
            histogram_gray(src, hist);
            int nzCount = cv::countNonZero(src);
            printf("\t the number of non zero pixels is = %d of total %d pizels \n", nzCount, height * width);
        }
        else if (type >= 2)
        {
            histogram_color(src, hist);
        }
        dst= hist;
    }
    catch (cv::Exception& e)
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
    return 0;
}

int main()
{	
    bool show = true;
    int delay_show = 10000;
    
    if (show)
    {

        cv::Mat dst;
        cv::Mat src=cv::imread("a.png");
        cv::imshow("main image ", src);
        cv::waitKey(delay_show);
        func_image_info(src, dst);
        cv::imshow("histogram of image ", dst);
        cv::waitKey(delay_show);
	    
    }
}
