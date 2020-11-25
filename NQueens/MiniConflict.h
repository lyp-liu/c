#ifndef MINICONFLICT_H
#define MINICONFLICT_H
#include <iostream>
#include <random>
#include <vector>
#include <time.h>
#define MAX 6000//最多可能皇后数
//#define swap(a,b){int t=a;a=b;b=t;}
using namespace std;

class MiniConflict
{
public:
    MiniConflict(int n);
    vector<vector<string>> solveNQueens();
    int row[MAX];//当前摆放方式下第i行皇后数
    int col[MAX];//当前摆放方式第i列皇后数
    int pdiag[2*MAX];//主对角线上元素row-col值相同，但是可能为负值最小为-（N-1）
                       //做一个偏移，在此值基础加一个N-1，结果的范围在[0，2*N-2]
                        //作为对角线的编号pdiag[i]表示编号为i的对角线上皇后数
    int cdiag[2*MAX];//副对角线上元素row+col值相同，作为对角线编号，范围[0,2*N-2]
    int R[MAX];//存储皇后的位置：R[row]=col表示第row行第col列有皇后
    bool adjust_row(int row); // 调整下第row行的皇后的位置
    //void print_result(); // 输出结果
    bool qualify(); //验证是否正确
    void init();//初始化皇后的摆放，同时初始化row,col,pdiag,cdiag数组
    //给定二维矩阵的一个点坐标，返回其对应的左上到右下的对角线编号
    int getP(int row, int col);
    //给定二维矩阵的一个点坐标，返回其对应的右上到左下的对角线编号
    int getC(int row, int col);
    void convert();
    double getTime() { return time_t; }
private:
    vector<vector<string>> res;
    double time_t;
    int n;
};

#endif // MINICONFLICT_H
