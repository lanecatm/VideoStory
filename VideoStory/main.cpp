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
#include "KMeans.hpp"
using namespace std;
using namespace cv;

int main(){
    int dimNum = 3;
    
    FlowCompare flowComp = FlowCompare();
    FrameGetter frameGetter = FrameGetter();
    
    //读入视频
    string videoPath1 = "/Users/xfhuang/code/Resources/opencv/v1.m4v";
    string videoPath2 = "/Users/xfhuang/code/Resources/opencv/v2.m4v";
    string videoPath3 = "/Users/xfhuang/code/Resources/opencv/v3.m4v";
    string videoPath4 = "/Users/xfhuang/code/Resources/opencv/v4.m4v";
    string videoPath5 = "/Users/xfhuang/code/Resources/opencv/v5.m4v";
    string videoPath6 = "/Users/xfhuang/code/Resources/opencv/v6.m4v";
    string videoPath7 = "/Users/xfhuang/code/Resources/opencv/v7.m4v";
    string videoPath8 = "/Users/xfhuang/code/Resources/opencv/v8.m4v";
    string videoPath9 = "/Users/xfhuang/code/Resources/opencv/v9.m4v";
    string videoPath10 = "/Users/xfhuang/code/Resources/opencv/v10.m4v";
    string videoPath11 = "/Users/xfhuang/code/Resources/opencv/v11.m4v";
    string videoPath12 = "/Users/xfhuang/code/Resources/opencv/v12.m4v";
    
    
    //时间已经换算成百分比
    vector<pair<double, string>> timeAndVideoList;
    
    /*
    timeAndVideoList.push_back(pair<double, string>(0.0, videoPath1));
    timeAndVideoList.push_back(pair<double, string>(0.1, videoPath2));
     */
    timeAndVideoList.push_back(pair<double, string>(0.2, videoPath3));
    /*
    timeAndVideoList.push_back(pair<double, string>(0.3, videoPath4));
    timeAndVideoList.push_back(pair<double, string>(0.4, videoPath5));
    timeAndVideoList.push_back(pair<double, string>(0.5, videoPath6));
     */
    timeAndVideoList.push_back(pair<double, string>(0.6, videoPath7));
    /*
    timeAndVideoList.push_back(pair<double, string>(0.65, videoPath8));
     */
     
    timeAndVideoList.push_back(pair<double, string>(0.7, videoPath9));
    /*
    timeAndVideoList.push_back(pair<double, string>(0.8, videoPath10));
     */
    timeAndVideoList.push_back(pair<double, string>(0.85, videoPath11));
    timeAndVideoList.push_back(pair<double, string>(1, videoPath12));

    
    
    //导入视频并且计算光流
    vector<vector<Mat>> videoList;

    vector<double> flowStrengthList;
    vector<pair<double, string>>::iterator timeAndVideoIter;
    
    vector<double> timeList;
    
    for (timeAndVideoIter = timeAndVideoList.begin(); timeAndVideoIter < timeAndVideoList.end(); ++timeAndVideoIter){
        vector<Mat> videoClip = frameGetter.getFrameListFromVideo((*timeAndVideoIter).second, 10);
        double flowNum = flowComp.averageFlowStrengthFromImageList(videoClip);
        cout << "flow num: " << flowNum << endl;
        videoList.push_back(videoClip);
        flowStrengthList.push_back(flowNum);
        timeList.push_back((*timeAndVideoIter).first);
    }
    
    
    //光流归一化
    
    //计算图片颜色分布直方图的相似度
    ColorSimilarityComparer colorComparer = ColorSimilarityComparer();
    int startIndex = 0;
    vector<vector<Mat>>::iterator videoListIter;
    vector<Mat> startVideoImage = videoList[startIndex];
    vector<double> differenceList;
    int maxIndex = startIndex;
    int maxValue = 0;
    int index = 0;
    for(videoListIter = videoList.begin(); videoListIter < videoList.end(); ++videoListIter){
        double difference = colorComparer.compareImages(startVideoImage, *videoListIter);
        differenceList.push_back(difference);
        if (difference > maxValue){
            maxIndex = index;
            maxValue = difference;
        }
        ++index;
    }
    vector<int> indexToSelect;
    indexToSelect.push_back(startIndex);
    indexToSelect.push_back(maxIndex);
    cout << "start index:" << startIndex << endl;
    cout << "max Index:" << maxIndex << endl;
    
    
    //构建输入矩阵
    vector<Tuple> inputTuples;
    //读入数据
    int inputIndex;
    for(inputIndex=0; inputIndex<videoList.size(); ++inputIndex)
    {
        //第一个位置存放记录编号，第2到dimNum+1个位置存放实际元素
        Tuple tuple(dimNum+1, 0);
        tuple[0] = inputIndex + 1;
        tuple[1] = flowStrengthList[inputIndex];
        tuple[2] = differenceList[inputIndex];
        tuple[3] = timeList[inputIndex];
        inputTuples.push_back(tuple);
    }
    
    KMeans kmeans = KMeans();
    kmeans.onetimeKMeans(inputTuples, indexToSelect);

    
    
    
    
    
    
    //计算画面平均光流的值
    
    
    //获取视频中的序列
    
    //kmeams
    
    //时间就是视频序列的名称
    
    
    
    
    
    return 0;
}

