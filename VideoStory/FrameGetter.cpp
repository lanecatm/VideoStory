//
//  FrameGetter.cpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/11.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#include "FrameGetter.hpp"
using namespace std;
using namespace cv;

vector<Mat> FrameGetter::getFrameListFromVideo(string filename)
{
    vector<Mat> frameList;
    //要读取的视频文件
    VideoCapture capture(filename);
    if (!capture.isOpened()){
        cerr << "No file " << filename << endl;
        return frameList;
    }
    
    while (1) {
        Mat frame;
        if (!capture.read(frame))
            break;
        frameList.push_back(frame);
    }
    capture.release();
    cout << "get " << frameList.size() << " frames from " << filename << endl;
    return frameList;
}

Mat FrameGetter::getFrameFromImage(string filename)
{
    Mat image = imread(filename);
    if(!image.data)
    {
        cerr << "No file " << filename << endl;
    }
    return image;
}

vector<Mat> FrameGetter::getKeyFrameListFromVideo(string filename)
{
    vector<Mat> frameList = getFrameListFromVideo(filename);
    return getKeyFrameList(frameList);
}


vector<Mat> FrameGetter::getKeyFrameList(vector<Mat> frameList)
{
    vector<Mat> keyFrameList;
    //TODO 传入一个color分析类，并且做分析keyFrame
    return keyFrameList;
}
