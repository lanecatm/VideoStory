
//
//  main.cpp
//  OpencvTest
//
//  Created by 黄晓芙 on 16/12/13.
//  Copyright © 2016年 黄晓芙. All rights reserved.
//
//#include <iostream>
//#include "opencv2/opencv.hpp"
//#include <stdio.h>
//#include "opencv2/core/core.hpp"
//#include "opencv2/features2d/features2d.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/nonfree/nonfree.hpp"
//#include "opencv2/legacy/legacy.hpp"

//using namespace cv;
//using namespace std;
/*
#define UNKNOWN_FLOW_THRESH 1e9

void makecolorwheel(vector<Scalar> &colorwheel)
{
    int RY = 15;
    int YG = 6;
    int GC = 4;
    int CB = 11;
    int BM = 13;
    int MR = 6;
    
    int i;
    
    for (i = 0; i < RY; i++) colorwheel.push_back(Scalar(255,       255*i/RY,     0));
    for (i = 0; i < YG; i++) colorwheel.push_back(Scalar(255-255*i/YG, 255,       0));
    for (i = 0; i < GC; i++) colorwheel.push_back(Scalar(0,         255,      255*i/GC));
    for (i = 0; i < CB; i++) colorwheel.push_back(Scalar(0,         255-255*i/CB, 255));
    for (i = 0; i < BM; i++) colorwheel.push_back(Scalar(255*i/BM,      0,        255));
    for (i = 0; i < MR; i++) colorwheel.push_back(Scalar(255,       0,        255-255*i/MR));
}
void motionToColor(Mat flow, Mat &color)
{
    if (color.empty())
        color.create(flow.rows, flow.cols, CV_8UC3);
    
    static vector<Scalar> colorwheel; //Scalar r,g,b
    if (colorwheel.empty())
        makecolorwheel(colorwheel);
    
    // determine motion range:
    float maxrad = -1;
    
    // Find max flow to normalize fx and fy
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            Vec2f flow_at_point = flow.at<Vec2f>(i, j);
            float fx = flow_at_point[0];
            float fy = flow_at_point[1];
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
                continue;
            float rad = sqrt(fx * fx + fy * fy);
            maxrad = maxrad > rad ? maxrad : rad;
        }
    } for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            uchar *data = color.data + color.step[0] * i + color.step[1] * j;
            Vec2f flow_at_point = flow.at<Vec2f>(i, j);
            
            float fx = flow_at_point[0] / maxrad;
            float fy = flow_at_point[1] / maxrad;
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
            {
                data[0] = data[1] = data[2] = 0;
                continue;
            }
            float rad = sqrt(fx * fx + fy * fy);
            
            float angle = atan2(-fy, -fx) / CV_PI;
            float fk = (angle + 1.0) / 2.0 * (colorwheel.size()-1);
            int k0 = (int)fk;
            int k1 = (k0 + 1) % colorwheel.size();
            float f = fk - k0;
            //f = 0; // uncomment to see original color wheel
            
            for (int b = 0; b < 3; b++)
            {
                float col0 = colorwheel[k0][b] / 255.0;
                float col1 = colorwheel[k1][b] / 255.0;
                float col = (1 - f) * col0 + f * col1;
                if (rad <= 1)
                    col = 1 - rad * (1 - col); // increase saturation with radius
                else
                    col *= .75; // out of range
                data[2 - b] = (int)(255.0 * col);
            }
        }  
    }  
}
void motionToColor1(Mat flow, Mat &color)
{
    if (color.empty())
        color.create(flow.rows, flow.cols, CV_8UC3);

    // Find max flow to normalize fx and fy
    for (int i= 0; i < flow.rows; ++i)
    {
        for (int j = 0; j < flow.cols; ++j)
        {
            uchar *data = color.data + color.step[0] * i + color.step[1] * j;
            Vec2f flow_at_point = flow.at<Vec2f>(i, j);
            float fx = flow_at_point[0];
            float fy = flow_at_point[1];
            if ((fabs(fx) >  UNKNOWN_FLOW_THRESH) || (fabs(fy) >  UNKNOWN_FLOW_THRESH))
                continue;
            data[0]=(int)fx/10 > 255 ? 255 : (int)fx/10;
            data[1]=(int)fy/10 > 255 ? 255 : (int)fy/10;
        }
    }
}
//计算原始图像点位在经过矩阵变换后在目标图像上对应位置
Point2f getTransformPoint(const Point2f originalPoint,const Mat &transformMaxtri)
{
    Mat originelP,targetP;
    originelP=(Mat_<double>(3,1)<<originalPoint.x,originalPoint.y,1.0);
    targetP=transformMaxtri*originelP;
    float x=targetP.at<double>(0,0)/targetP.at<double>(2,0);
    float y=targetP.at<double>(1,0)/targetP.at<double>(2,0);
    return Point2f(x,y);
}


int main(int, char**)
{
    //VideoCapture cap;
    //cap.open(0);
    //cap.open("test_02.wmv");


    Mat gray1, gray2, flow, flow2;
    namedWindow("flow", 1);

    Mat motion2color;

    //Mat img1 = imread("/Users/xfhuang/code/Resources/opencv/7.png");
    Mat img1 = imread("/Users/xfhuang/code/Resources/opencv/m2.png");

    if(!img1.data)
    {
        printf("No data!--Exiting the program \n");
        return -1;
    }
    //Mat img2 = imread("/Users/xfhuang/code/Resources/opencv/8.png");
    Mat img2 = imread("/Users/xfhuang/code/Resources/opencv/m7.png");

    if(!img2.data)
    {
        printf("No data!--Exiting the program \n");
        return -1;
    }
    resize(img1, img1, Size(img1.cols*0.25,img1.rows*0.25));
    resize(img2, img2, Size(img2.cols*0.25,img2.rows*0.25));
    imshow("original1", img1);
    imshow("original2", img2);
    //for(;;)
    //{
    //double t = (double)cvGetTickCount();

    //cap >> frame;
    cvtColor(img1, gray1, CV_BGR2GRAY);
    cvtColor(img2, gray2, CV_BGR2GRAY);


    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
    motionToColor(flow, motion2color);
    imshow("flow", motion2color);
 
 
 
    SurfFeatureDetector detector(400);
    vector<KeyPoint> keypoints1, keypoints2;
    detector.detect(img1, keypoints1);
    detector.detect(img2, keypoints2);

    // computing descriptors
    SurfDescriptorExtractor extractor;
    Mat descriptors1, descriptors2;
    extractor.compute(img1, keypoints1, descriptors1);
    extractor.compute(img2, keypoints2, descriptors2);


    //获得匹配特征点，并提取最优配对
    FlannBasedMatcher matcher;
    vector<DMatch> matchePoints;
    matcher.match(descriptors1,descriptors2,matchePoints,Mat());
    sort(matchePoints.begin(),matchePoints.end()); //特征点排序
    //获取排在前N个的最优匹配特征点
    vector<Point2f> imagePoints1,imagePoints2;
    for(int i=0;i<10;i++)
    {
        imagePoints1.push_back(keypoints1[matchePoints[i].queryIdx].pt);
        imagePoints2.push_back(keypoints2[matchePoints[i].trainIdx].pt);
    }
    //获取图像1到图像2的投影映射矩阵，尺寸为3*3
    Mat homo=findHomography(imagePoints1,imagePoints2,CV_RANSAC);
    Mat adjustMat=(Mat_<double>(3,3)<<1.0,0,img1.cols,0,1.0,0,0,0,1.0);
    Mat adjustHomo=adjustMat*homo;
    
    //图像配准
    Mat imageTransform1;
    warpPerspective(img1,imageTransform1,homo, img1.size());
    namedWindow("changed img1", 1);
    imshow("changed img1", imageTransform1);

    cvtColor(imageTransform1, gray1, CV_BGR2GRAY);
    cvtColor(img2, gray2, CV_BGR2GRAY);
    
    
    calcOpticalFlowFarneback(gray1, gray2, flow2, 0.5, 3, 15, 3, 5, 1.2, 0);
    motionToColor(flow2, motion2color);
    imshow("flow2", motion2color);

    
    // matching descriptors
    BFMatcher bfmatcher(NORM_L2);
    vector<DMatch> matches;
    bfmatcher.match(descriptors1, descriptors2, matches);

    // drawing the results
    namedWindow("matches", 1);
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
    
    imshow("matches", img_matches);
    waitKey(0);
    return 0;
}


//int main(int argc, char** argv)
//{
//    Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
//    Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
//    if(img1.empty() || img2.empty())
//    {
//        printf("Can't read one of the images\n");
//        return -1;
//    }
//
//    // detecting keypoints
//    SurfFeatureDetector detector(400);
//    vector<KeyPoint> keypoints1, keypoints2;
//    detector.detect(img1, keypoints1);
//    detector.detect(img2, keypoints2);
//
//    // computing descriptors
//    SurfDescriptorExtractor extractor;
//    Mat descriptors1, descriptors2;
//    extractor.compute(img1, keypoints1, descriptors1);
//    extractor.compute(img2, keypoints2, descriptors2);
//
//    // matching descriptors
//    BFMatcher matcher(NORM_L2);
//    vector<DMatch> matches;
//    matcher.match(descriptors1, descriptors2, matches);
//
//    // drawing the results
//    namedWindow("matches", 1);
//    Mat img_matches;
//    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
//    imshow("matches", img_matches);
//    waitKey(0);
//
//    return 0;
//}
 */
 /*
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp" 
#include <iostream> 
#include <stdio.h>  
using namespace std;
using namespace cv;
int main( int argc, char** argv )
{   Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;
    /// 装载三张背景环境不同的图像
    src_base = imread( "/Users/xfhuang/code/Resources/opencv/m3.png");
    src_test1 = imread( "/Users/xfhuang/code/Resources/opencv/m4.png");
    src_test2 = imread( "/Users/xfhuang/code/Resources/opencv/m7.png");
    /// 转换到 HSV
    cvtColor( src_base, hsv_base, CV_BGR2HSV );
    cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
    cvtColor( src_test2, hsv_test2, CV_BGR2HSV );
    hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
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
    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;
    /// 计算HSV图像的直方图
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
    normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );
    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );
    
    ///应用不同的直方图对比方法
    for( int i = 0; i < 4; i++ )
    {
        int compare_method = i;
        double base_base = compareHist( hist_base, hist_base, compare_method );
        double base_half = compareHist( hist_base, hist_half_down, compare_method );
        double base_test1 = compareHist( hist_base, hist_test1, compare_method );
        double base_test2 = compareHist( hist_base, hist_test2, compare_method );
        printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
    }
    printf( "Done \n" );
    return 0;
}
 */
