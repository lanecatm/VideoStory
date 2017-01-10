//
//  ColorSimilarityComparer.cpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/10.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#include "ColorSimilarityComparer.hpp"
using namespace std;
using namespace cv;


double ColorSimilarityComparer::compareTwoImage(const Mat &image1, const Mat &image2, int compareMethod)
{
    Mat hsvImage1, hsvImage2;
    /// 转换到 HSV
    cvtColor( image1, hsvImage1, CV_BGR2HSV );
    cvtColor( image2, hsvImage2, CV_BGR2HSV );
    /// 对hue通道使用30个bin,对saturatoin通道使用32个bin
    int h_bins = 50;
    int s_bins = 60;
    int histSize[] = { h_bins, s_bins };
    // hue的取值范围从0到256, saturation取值范围从0到180
    float h_ranges[] = { 0, 256 };
    float s_ranges[] = { 0, 180 };
    const float* ranges[] = { h_ranges, s_ranges };
    // 使用第0和第1通道
    int channels[] = { 0, 1 };
    /// 直方图
    MatND histImage1;
    MatND histImage2;
    /// 计算HSV图像的直方图
    calcHist( &hsvImage1, 1, channels, Mat(), histImage1, 2, histSize, ranges, true, false );
    normalize( histImage1, histImage1, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsvImage2, 1, channels, Mat(), histImage2, 2, histSize, ranges, true, false );
    normalize( histImage2, histImage2, 0, 1, NORM_MINMAX, -1, Mat() );
    
    ///应用不同的直方图对比方法
    double result = 1 - compareHist( histImage1, histImage2, compareMethod );
    return result;
}

double ColorSimilarityComparer::compareImages(const vector<Mat> imageList1, const vector<Mat> imageList2, int compareMethod)
{
    
    return 0;
    
}