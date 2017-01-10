//
//  FlowCompare.cpp
//  OpencvTest
//
//  Created by 黄晓芙 on 17/1/9.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#include "FlowCompare.hpp"
using namespace std;
using namespace cv;

FlowCompare::FlowCompare()
{
    
}


void FlowCompare::estimateCameraMoving(const Mat &img1, const Mat &img2, Mat &changedImg1)
{
    
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
    warpPerspective(img1, changedImg1, homo, img1.size());

}

void FlowCompare::compareOpticalFlow(const Mat &img1, const Mat &img2, Mat &flow)
{
    Mat gray1, gray2;
    cvtColor(img1, gray1, CV_BGR2GRAY);
    cvtColor(img2, gray2, CV_BGR2GRAY);
    calcOpticalFlowFarneback(gray1, gray2, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
}

void FlowCompare::makeColorWheel(vector<Scalar> &colorwheel)
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

void FlowCompare::showResult(const Mat &flow, Mat &color)
{
    if (color.empty())
        color.create(flow.rows, flow.cols, CV_8UC3);
    
    static vector<Scalar> colorwheel; //Scalar r,g,b
    if (colorwheel.empty())
        makeColorWheel(colorwheel);
    
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
    }
    for (int i= 0; i < flow.rows; ++i)
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




//计算原始图像点位在经过矩阵变换后在目标图像上对应位置
Point2f FlowCompare::getTransformPoint(const Point2f &originalPoint,const Mat &transformMaxtri)
{
    Mat originelP,targetP;
    originelP=(Mat_<double>(3,1)<<originalPoint.x,originalPoint.y,1.0);
    targetP=transformMaxtri*originelP;
    float x=targetP.at<double>(0,0)/targetP.at<double>(2,0);
    float y=targetP.at<double>(1,0)/targetP.at<double>(2,0);
    return Point2f(x,y);
}
