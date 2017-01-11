//
//  FlowCompare.hpp
//  OpencvTest
//
//  Created by 黄晓芙 on 17/1/9.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#ifndef FlowCompare_hpp
#define FlowCompare_hpp

#include <iostream>
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


#define UNKNOWN_FLOW_THRESH 1e9



class FlowCompare{
public:
    FlowCompare();
    
    //消除相机移动
    void estimateCameraMoving(const cv::Mat &img1, const cv::Mat &img2, cv::Mat &changedImg1);
    
    //比较光流
    void compareOpticalFlow(const cv::Mat &img1, const cv::Mat &img2, cv::Mat &flow);
    
    //展现单幅光流示意图
    void showResult(const cv::Mat &flow, cv::Mat &color);
    
    //仅计算光流的强度
    double averageFlowStrength(const std::vector<cv::Mat> flow);
    
    //计算光流的向量
    void averageFlow
    
    
private:
    //计算显示光流的色轮
    void makeColorWheel(std::vector<cv::Scalar> &colorwheel);
    
    //计算原始图像点位在经过矩阵变换后在目标图像上对应位置
    cv::Point2f getTransformPoint(const cv::Point2f &originalPoint,const cv::Mat &transformMaxtri);

    
};

#endif /* FlowCompare_hpp */
