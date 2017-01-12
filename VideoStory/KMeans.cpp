//
//  kmeans.cpp
//  VideoStory
//
//  Created by 黄晓芙 on 17/1/11.
//  Copyright © 2017年 黄晓芙. All rights reserved.
//

#include "KMeans.hpp"
using namespace std;


vector<vector<Tuple>> KMeans::onetimeKMeans(vector<Tuple>& tuples, const vector<int> &indexToSelect){
    cout<<"in kmeans" << endl;
    //k个簇
    vector<vector<Tuple>> clusters;
    //k个中心点
    vector<Tuple> means;

    int kNum = 0;
    for (kNum = 0; kNum < k; ++kNum){
        vector<Tuple> cluster;
        clusters.push_back(cluster);
        Tuple center;
        means.push_back(center);
    }
    
    cout << "choose center" << endl;
    int i=0;
    //一开始随机选取k条记录的值作为k个簇的质心（均值）
    for(i=0;i<k;++i){
        int iToSelect = indexToSelect[i];
        if(means[i].size() == 0)
        {
            for(int j=0; j<=dimNum; ++j)
            {
                means[i].push_back(tuples[iToSelect][j]);
            }
        }
        else{
            cout << "error size" << endl;
        }
    }
    cout << "finish center" << endl;

    int lable=0;
    //根据默认的质心给簇赋值
    for(i=0;i!=tuples.size();++i){
        lable=clusterOfTuple(means,tuples[i]);
        clusters[lable].push_back(tuples[i]);
    }
    double oldVar=-1;
    double newVar=getVar(clusters,means);
    cout<<"初始的的整体误差平方和为："<<newVar<<endl;
    int t = 0;
    while(abs(newVar - oldVar) >= 1) //当新旧函数值相差不到1即准则函数值不发生明显变化时，算法终止
    {
        cout<<"第 "<<++t<<" 次迭代开始："<<endl;
        for (i = 0; i < k; i++) //更新每个簇的中心点
        {
            means[i] = getMeans(clusters[i]);
        }
        oldVar = newVar;
        newVar = getVar(clusters,means); //计算新的准则函数值
        for (i = 0; i < k; i++) //清空每个簇
        {
            clusters[i].clear();
        }
        //根据新的质心获得新的簇
        for(i=0; i!=tuples.size(); ++i){
            lable=clusterOfTuple(means,tuples[i]);
            clusters[lable].push_back(tuples[i]);
        }
        cout<<"此次迭代之后的整体误差平方和为："<<newVar<<endl;
    }

    cout<<"The result is:\n";
    print(clusters);
    return clusters;
}

//计算两个元组间的欧几里距离
double KMeans::getDistXY(const Tuple& t1, const Tuple& t2)
{
    double sum = 0;
    for(int i=1; i<=dimNum; ++i)
    {
        sum += (t1[i]-t2[i]) * (t1[i]-t2[i]);
    }
    return sqrt(sum);
}

//根据质心，决定当前元组属于哪个簇
int KMeans::clusterOfTuple(vector<Tuple> means,const Tuple& tuple){
    double dist=getDistXY(means[0],tuple);
    double tmp;
    int label=0;//标示属于哪一个簇
    for(int i=1;i<k;i++){
        tmp=getDistXY(means[i],tuple);
        if(tmp<dist) {dist=tmp;label=i;}
    }
    return label;
}
//获得给定簇集的平方误差
double KMeans::getVar(vector<vector<Tuple>> clusters,vector<Tuple> means){
    double var = 0;
    for (int i = 0; i < k; i++)
    {
        vector<Tuple> t = clusters[i];
        for (int j = 0; j< t.size(); j++)
        {
            var += getDistXY(t[j],means[i]);
        }
    }
    //cout<<"sum:"<<sum<<endl;
    return var;

}
//获得当前簇的均值（质心）
Tuple KMeans::getMeans(const vector<Tuple>& cluster){

    int num = cluster.size();
    Tuple t(dimNum+1, 0);
    for (int i = 0; i < num; i++)
    {
        for(int j=1; j<=dimNum; ++j)
        {
            t[j] += cluster[i][j];
        }
    }
    for(int j=1; j<=dimNum; ++j)
        t[j] /= num;
    return t;
    //cout<<"sum:"<<sum<<endl;
}

void KMeans::print(const vector<vector<Tuple>> clusters)
{
    for(int lable=0; lable<k; lable++)
    {
        cout<<"第"<<lable+1<<"个簇："<<endl;
        vector<Tuple> t = clusters[lable];
        for(int i=0; i<t.size(); i++)
        {
            cout<<i+1<<".(";
            for(int j=0; j<=dimNum; ++j)
            {
                cout<<t[i][j]<<", ";
            }
            cout<<")\n";
        }
    }
}
/*
int xmain(){
    //样本数目dataNum
    int dataNum;
    //维数dimNum


    vector<Tuple> tuples;
    //读入数据
    for(int i=0; i<dataNum; ++i)
    {
        //第一个位置存放记录编号，第2到dimNum+1个位置存放实际元素
        Tuple tuple(dimNum+1, 0);
        tuple[0] = i+1;
        for(int j=1; j<=dimNum; ++j)
        {
            //TODO change input
            tuple[j] = 0;
        }
        tuples.push_back(tuple);
    }

    KMeans(tuples);
    return 0;
}
*/
