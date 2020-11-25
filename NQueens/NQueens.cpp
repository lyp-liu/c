#include "NQueens.h"

NQueens::NQueens()
{
    //构造函数
}

NQueens::~NQueens()
{
    //析构函数
}

//转向对应算法
vector<vector<string>> NQueens::solveNQueens(int n, int algorithm) {
    // '.' 表示空，'Q' 表示皇后，初始化空棋盘。
    if(algorithm == 0){
        //最小冲突法
        MiniConflict queen(n);
        vector<vector<string>> res=queen.solveNQueens();
        time=queen.getTime();
        return res;
    }
    else if(algorithm==1){
        //遗传算法
        Genetic queen(n);
        vector<vector<string>> res = queen.GeneticCalculation();
        time = queen.getTime();
        return res;
    }
    else if (algorithm == 2){
        //爬山法
        HillClimbing queen(n);
        vector<vector<string>> res = queen.solveNQueens();
        time = queen.getTime();
        return res;
    }

}
