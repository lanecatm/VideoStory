//
//  KMeans.hpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/11.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#ifndef KMeans_hpp
#define KMeans_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "opencv2/opencv.hpp"


//存放元组的属性信息
typedef std::vector<double> Tuple;

class KMeans{
public:

    KMeans(int _dimNum = 3, int _k = 2)
    {
        k = _k;
        dimNum = _dimNum;
    }
    
    std::vector<std::vector<Tuple>> onetimeKMeans(std::vector<Tuple>& tuples, const std::vector<int> &indexToSelect);
    
private:
    int dimNum;//每条记录的维数
    int k;
    //计算两个元组间的欧几里距离
    double getDistXY(const Tuple& t1, const Tuple& t2);
    
    //根据质心，决定当前元组属于哪个簇
    int clusterOfTuple(std::vector<Tuple> means,const Tuple& tuple);
    
    //获得给定簇集的平方误差
    double getVar(std::vector<std::vector<Tuple>> clusters,std::vector<Tuple> means);
    
    //获得当前簇的均值（质心）
    Tuple getMeans(const std::vector<Tuple>& cluster);
    
    void print(const std::vector<std::vector<Tuple>> clusters);
};


#endif /* KMeans_hpp */
