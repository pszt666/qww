//
// Created by dell on 2023/2/9.
//
#ifndef EXTERNALSORT_FUNCTONS_H
#define EXTERNALSORT_FUNCTONS_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;
#define MAX_NUM 3  //内存最大数目
#define MAX 1e9    //表示是最大值
#define MERGE_NUM 2//每次归并数目，从小到大开始尝试
typedef struct
{
    double num;//存放当前数的大小
    int rnum;  //所属归并段的段号
} LEAFNODE;
extern int CNT;                         //表示读取了多少数据
extern int DATA_NUM;                    //表示数据量
extern vector<double> TT;               //将文件中的数据读取到TT中
extern vector<vector<double>> mergearea;//测试用，存储归并段
extern vector<int> areasize;            //每个归并段数目存储，用于建立哈弗曼树
bool cmp(const vector<double> &a, const vector<double> &b);
void judgetree(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM], int q);                                      //更新败者树
void buildtree(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM]);                                             //构建败者树函数
void get_run(int ls[MAX_NUM], LEAFNODE wa[MAX_NUM], int rc, int *rmax);                            //开始败者树划分归并段的流程
void replace_selection();                                                                          //归并选择
void judgetree1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], int q);                                 //q表示刚刚更改的标志位位置
void buildtree1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], vector<vector<double>> process);        //构建败者树2函数
vector<double> get_run1(int ls[MERGE_NUM], LEAFNODE wa[MERGE_NUM], vector<vector<double>> process);//开始败者树合并归并段的流程
vector<double> merge(vector<vector<double>> process);                                              //使用败者树进行段的归并
void savearea();                                                                                   //保存所有数据分成的归并段数目以及各段数据
void savefile(vector<double> res);                                                                 //输出结果文件
void readfile();                                                                                   //读取初始文件的数据
void huffman();                                                                                    //利用huffman树来减小读写外存的次数，k的选值十分重要
#endif                                                                                             //EXTERNALSORT_FUNCTONS_H
