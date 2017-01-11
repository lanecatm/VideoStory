//
//  FrameGetter.hpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/11.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#ifndef FrameGetter_hpp
#define FrameGetter_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <string>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


class FrameGetter{
public:
    std::vector<cv::Mat> getFrameListFromVideo(std::string filename);
    cv::Mat getFrameFromImage(std::string filename);
    std::vector<cv::Mat> getKeyFrameListFromVideo(std::string filename);
    std::vector<cv::Mat> getKeyFrameList(std::vector<cv::Mat> frameList);

};


#endif /* FrameGetter_hpp */
