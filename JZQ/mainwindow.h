#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QLabel>
#include <QtWidgets>
#include<time.h>
#include<ctime>
#define COM 1
#define MAN -1
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int count1=0;

private:
    Ui::MainWindow *ui;

    struct Move{
        //棋子位置
        int x;
        int y;
    };

    int firstmover;//0为机器先手1为人先手
    QRadioButton *rBtnManVSCom,*rBtnComVSCom;
    int player;//当前下子方
    //是否圈一方下子
    bool circle;
    //当前深度
    int currentDepth;
    //游戏类型 0为人机1为电脑-电脑
    int gametype;
    // 圈的棋盘
    int _cirCleMapNum[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };
    // 叉的棋盘
    int _crossMapNum[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
    };

    //棋盘
    int board[3][3] = {
        { 0,0,0 },
        { 0,0,0 },
        { 0,0,0 }
    };

    // 临时棋盘
    int tempBoard[3][3] = {
        { 0,0,0 },
        { 0,0,0 },
        { 0,0,0 }
    };
    bool sx1;//人工智障先下
    bool sx2;//人工智能先下
    Move bestMove;//最好的一步
    int a_getMoveList(Move moveList[]);
    void a_makeMove(Move curMove);
    void a_unMakeMove(Move curMove);
    int a_man_play(QPushButton *btn);
    int a_com_play();
    int a_zz_play();
    void clearMapNum();
    void ManVSCom(QPushButton *btn);
    void ComVSCom();
    int a_isWin();
    bool a_isDraw();
    int Evaluation();//评估函数,计算每一行、每一列、斜线中连成3个棋子的有多少个
    int AlphaBeta(int alpha,int beta,int depth);//剪枝算法
    QList<QPushButton *> btnList;
public slots:
    void btnClick();
    void ending();
    void radioBtnClick();
private slots:
    int on_pushButton_clicked();
};

#endif // MAINWINDOW_H
