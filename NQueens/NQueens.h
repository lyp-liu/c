#ifndef NQUEENS_H
#define NQUEENS_H

#include <iostream>
#include <string>
#include <vector>


#include "Genetic.h"

#include "HillClimbing.h"
#include "MiniConflict.h"
using namespace std;

class NQueens
{
public:
    NQueens();
    ~NQueens();
    vector<vector<string>> solveNQueens(int n, int algorithm);//返回查找到的结果
    double getTime(){return time;}
private:
    double time;
};

#endif // NQUEENS_H
