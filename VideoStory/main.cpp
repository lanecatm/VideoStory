//
//  main.cpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/10.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#include <string>
#include "FlowCompare.hpp"
#include "ColorSimilarityComparer.hpp"
#include "FrameGetter.hpp"
using namespace std;
using namespace cv;

int main(){
    
    FlowCompare flowComp = FlowCompare();
    FrameGetter frameGetter = FrameGetter();
    
    //读入图片
    string img1Path = "/Users/xfhuang/code/Resources/opencv/11.png";
    string img2Path = "/Users/xfhuang/code/Resources/opencv/12.png";
    
    //读入视频
    string videoPath1 = "/Users/xfhuang/code/Resources/opencv/v1.m4v";
    vector<Mat> video1List = frameGetter.getFrameListFromVideo(videoPath1);
    
    Mat img1 = frameGetter.getFrameFromImage(img1Path);
    if(!img1.data)
    {
        return -1;
    }
    
    Mat img2 = frameGetter.getFrameFromImage(img2Path);
    if(!img2.data)
    {
        return -1;
    }
    
    //原图太大，缩小一下
    resize(img1, img1, Size(img1.cols*0.25,img1.rows*0.25));
    resize(img2, img2, Size(img2.cols*0.25,img2.rows*0.25));
    imshow("original1", img1);
    imshow("original2", img2);
    cvWaitKey(0);
    
    //光流
    Mat motion2color, flow;
    flowComp.compareOpticalFlow(img1, img2, flow);
    flowComp.showResult(flow, motion2color);
    imshow("flow", motion2color);
    cvWaitKey(0);

    
    //修改图片1的位移并光流
    Mat estimateCameraMovingImg1, estimateCameraMovingFlow, estimateCameraMoving2Color;
    flowComp.estimateCameraMoving(img1, img2, estimateCameraMovingImg1);
    imshow("extimate moving", estimateCameraMovingImg1);
    cvWaitKey(0);
    flowComp.compareOpticalFlow(img1 , img2, estimateCameraMovingFlow);
    flowComp.showResult(estimateCameraMovingFlow, estimateCameraMoving2Color);
    imshow("estimate_camera_moving", estimateCameraMoving2Color);
    cvWaitKey(0);
    
    //计算图片颜色分布直方图的相似度
    ColorSimilarityComparer colorComparer = ColorSimilarityComparer();
    cout << "same image:" << colorComparer.compareTwoImage(img1, img1)<< endl;
    cout << "different image:" << colorComparer.compareTwoImage(img1, img2)<<endl;
    
    
    
    //计算画面平均光流的值
    
    
    //获取视频中的序列
    
    //kmeams
    
    //时间就是视频序列的名称
    
    
    
    
    
    return 0;
}

