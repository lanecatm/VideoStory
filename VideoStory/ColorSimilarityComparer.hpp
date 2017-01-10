//
//  ColorSimilarityComparer.hpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/10.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#ifndef ColorSimilarityComparer_hpp
#define ColorSimilarityComparer_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


class ColorSimilarityComparer{
public:
    double compareTwoImage(const cv::Mat &image1, const cv::Mat &image2, int compareMethod = 0);
    
    double compareImages(const std::vector<cv::Mat> imageList1, const std::vector<cv::Mat> imageList2, int compareMethod = 0);
    
    
};

#endif /* ColorSimilarityComparer_hpp */
