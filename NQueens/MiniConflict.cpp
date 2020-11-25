#include "MiniConflict.h"
#include<ctime>
MiniConflict::MiniConflict(int al)
{
    n=al;
}
//给定二维矩阵的一个点坐标，返回其对应的左上到右下的对角线编号
int MiniConflict::getP(int row, int col) {
    return row - col + n - 1;
}

//给定二维矩阵的一个点坐标，返回其对应的右上到左下的对角线编号
int MiniConflict::getC(int row, int col) {
    return row + col;
}
void MiniConflict::init(){
        for (int i = 0; i < n; i++) {//N queens
            R[i] = i;
        }
        //初始化N个皇后对应的R数组为0~N-1的一个排列，即没有任意皇后同列，也没有任何皇后同行
        for (int i = 0; i < n; i++) {
            row[i] = 1;//每行恰好一个皇后
            col[i] = 0;//下面再做初始化的
        }
        for (int i = 0; i < 2 * n - 1; i++) {//N queens
            pdiag[i] = 0;
            cdiag[i] = 0;
        }
        for (int i = 0; i < n; i++) {//N queens
            col[R[i]]++;
            pdiag[getP(i, R[i])]++;
            cdiag[getC(i, R[i])]++;
        }
}
bool MiniConflict::adjust_row(int row) {
    int cur_col = R[row]; // 通过行得到列
    int optimal_col = cur_col;// 最佳列号，设置为当前列，然后更新
    int min_conflict = col[optimal_col]      // col不减一的原因是交换任然保证每行每列都有一个而已
        + pdiag[getP(row, optimal_col)] - 1  // 现在还没移过去
        + cdiag[getC(row, optimal_col)] - 1; // 对角线冲突数为当前对角线皇后数减一
    for (int i = 0; i < n; i++) {//逐个检查第row行的每个位置
        if (i == cur_col) continue; // 重复就跳过了
        int conflict = col[i] + pdiag[getP(row, i)] + cdiag[getC(row, i)];
        if (conflict < min_conflict) { // 因为之前这个点还没有移动，所以到这之后肯定是还会
            min_conflict = conflict;
            optimal_col = i;
        }
    }
    if (optimal_col != cur_col) {//要更新col,pdiag,cdiag
        col[cur_col]--;
        pdiag[getP(row, cur_col)]--;
        cdiag[getC(row, cur_col)]--;

        col[optimal_col]++;
        pdiag[getP(row, optimal_col)]++;
        cdiag[getC(row, optimal_col)]++;
        R[row] = optimal_col;// 注意，这里我们没有移动 在这个列上的之前的那个行上的皇后
        if (col[cur_col] == 1 && col[optimal_col] == 1
            && pdiag[getP(row, optimal_col)] == 1 && cdiag[getC(row, optimal_col)] == 1) {
            return qualify();//qualify相对更耗时，所以只在满足上面基本条件后才检查
        }
    }
    //当前点就是最佳点，一切都保持不变
    return false;//如果都没变的话，肯定不满足终止条件，否则上一次就应该返回true并终止了
}
bool MiniConflict::qualify() {
    for (int i = 0; i <n; i++) {//N queens
        if (col[R[i]] != 1 ||
            pdiag[getP(i, R[i])] != 1 ||
            cdiag[getC(i, R[i])] != 1) {
            return false;
        }
    }
    return true;
}
void MiniConflict::convert() {

    vector<string> queen;
    for (int i = 0; i < n; i++) {
        string str;
        for (int j = 0; j < n; j++) {
            if (R[i] == j) {
                str += 'Q';
//                cout << "Q";
            }
            else {
                str += '.';
//                cout << ".";
            }
        }
//        cout << "\n";
        queen.push_back(str);
    }
//    cout << "\n";
    res.push_back(queen);
}



vector<vector<string>>MiniConflict:: solveNQueens(){
    clock_t start = clock();


    srand((unsigned)time(NULL));// 设置好随机数种子

        init();
        if (!qualify()) { // 如果初始表不满足的话
            bool can_terminate = false;
            while (!can_terminate) {
                for (int i = 0; i < n; i++) {
                    if (adjust_row(i)) {
                        can_terminate = true;
                        break;
                    }
                }
            }
        }
        convert();
        clock_t end = clock();
        time_t = (double)(end - start) / CLOCKS_PER_SEC;
        return res;
}
