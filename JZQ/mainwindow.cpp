#pragma execution_character_set("utf-8")
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
//人为圈，电脑为叉
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    circle(true),//令圈优先下
    sx1(false),
    sx2(false),
    currentDepth(9)//当前深度为9
{
    ui->setupUi(this);

    this->setWindowTitle(tr("井字棋"));
    this->setFixedSize(480,300);
    this->setWindowIcon(QIcon(":/logo.png"));

    //设置棋盘
    int btnX=0,btnY=0,btnW=100,btnH=100;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            QPushButton *btn=new QPushButton(this);
            btnList.push_back(btn);
            btnX=j*100;
            btnY=i*100;
            btn->setGeometry(btnX,btnY,btnW,btnH);
            btn->setStyleSheet("border-image: url(:/grid.png);");
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClick()));
        }
    }

    // 重新开始

    QPushButton *resetBtn = new QPushButton(this);
    resetBtn->setGeometry(315, 15, 70, 30);
    resetBtn->setText(tr("重新开始"));
    connect(resetBtn, SIGNAL(clicked(bool)), this, SLOT(ending()));

    //对战模式
    QLabel *labelMode=new QLabel(tr("对战模式"),this);
    labelMode->setGeometry(resetBtn->pos().x(),resetBtn->pos().y()+30,100,30);
    rBtnManVSCom=new QRadioButton(tr("人类VS人工智能"),this);
    rBtnManVSCom->setStyleSheet({"color:rgb(0,191,255)"});
    rBtnManVSCom->setGeometry(labelMode->pos().x(), labelMode->pos().y() + 15,130,30);
    rBtnManVSCom->setChecked(true);//设置选中，默认为人机对战
    connect(rBtnManVSCom, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));

    rBtnComVSCom=new QRadioButton(tr("人工智障VS人工智能"),this);
    rBtnComVSCom->setStyleSheet({"color:rgb(0,0,255)"});
    rBtnComVSCom->setGeometry(rBtnManVSCom->pos().x(), rBtnManVSCom->pos().y() + 15, 160, 30);
    connect(rBtnComVSCom, SIGNAL(clicked(bool)), this, SLOT(radioBtnClick()));

    ui->pushButton->setEnabled(false);
    QButtonGroup * ModeGroup = new QButtonGroup(this);
    ModeGroup->addButton(rBtnManVSCom);
    ModeGroup->addButton(rBtnComVSCom);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::radioBtnClick(){
    QRadioButton *btn = qobject_cast<QRadioButton*>(sender());
    if(btn->text()=="人类VS人工智能"){
        gametype=0;
        qsrand(time(NULL));
        firstmover=qrand()%2;
        if(firstmover==1){
            player=MAN;
            QMessageBox::information(NULL,tr("提示"),tr("请您先手"));
        }
        else{
            player=COM;
            QMessageBox::information(NULL,tr("提示"),tr("人工智能先手"));
        }
        ending();
        if(player==COM){
            a_com_play();
            currentDepth--;
            player=MAN;
        }
    }
    else{
        ui->pushButton->setText("下一步棋");
        ui->pushButton->setEnabled(true);
        gametype=1;
        qsrand(time(NULL));
        firstmover=qrand()%2;
        if(firstmover==1){
            player=MAN;
            QMessageBox::information(NULL,tr("提示"),tr("人工智障先手"));
        }
        else{
            player=COM;
            QMessageBox::information(NULL,tr("提示"),tr("人工智能先手"));
        }
        ending();

    }


}
void MainWindow::btnClick(){
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(!gametype){//人机
        ManVSCom(btn);
    }
    /*else{//电脑-电脑
        ComVSCom();
    }*/

}

int MainWindow::a_com_play() {
    // 可以不需要接收返回的最好值，因为已经直接改掉了bestMove
    //获取当前深度的最佳下棋位置
    AlphaBeta(-1000,1000,2);//深度设置为两层
    //棋盘上bestmove位置更新为COM
   // cout<<count1;
    board[bestMove.x][bestMove.y] = COM;
    int place = (bestMove.x * 3) + bestMove.y;
    for (int i = 0; i < btnList.size(); i++) {
        if (i == place) {
            btnList[i]->setStyleSheet("border-image: url(:/fork.png);");
            btnList[i]->setEnabled(false);
        }
    }

    // 普通下子
    return 1;
}
void MainWindow::ManVSCom(QPushButton *btn){
    //人走棋
    int flag=a_man_play(btn);
    if(flag==1)
        currentDepth--;//深度减一
    if(a_isWin()==MAN){
        QMessageBox::information(this, tr("井字棋"), tr("你赢了！"), QMessageBox::Ok);
        ending();
        return;
    }
    else if(a_isDraw())
        return;
    else
        player = (player == COM) ? MAN : COM;

    //电脑走棋
    flag=a_com_play();
    if(flag==1)
        currentDepth--;

    //判断胜负
    if(a_isWin()==COM){
        QMessageBox::information(this, tr("井字棋"), tr("你输了！"), QMessageBox::Ok);
        ending();
        return;
    }
    else if (a_isDraw()) {
        return;

    }
    else
        player = (player == COM) ? MAN : COM;
}
void MainWindow::ComVSCom(){
    //人工智障走棋
    int flag=a_zz_play();
    if(flag==1)
        currentDepth--;
    if(a_isWin()==MAN){
        QMessageBox::information(this, tr("井字棋"), tr("人工智障赢了！"), QMessageBox::Ok);
        ending();
        return;
    }
    else if(a_isDraw())
        return;
    else
        player = (player == COM) ? MAN : COM;


    //电脑走棋
    flag=a_com_play();
    if(flag==1)
        currentDepth--;

    //判断胜负
    if(a_isWin()==COM){
        QMessageBox::information(this, tr("井字棋"), tr("人工智能赢了！"), QMessageBox::Ok);
        ending();
        return;
    }
    else if (a_isDraw()) {
        return;

    }
    else
        player = (player == COM) ? MAN : COM;

}
void MainWindow::ending(){
    QList<QPushButton *> ::iterator it;
    circle = true;
    for(it=btnList.begin();it!=btnList.end();it++)
    {
        // 需要把迭代器转成QPushButton
        QPushButton *btn = *it;
        btn->setStyleSheet("border-image: url(:/grid.png);");
        btn->setEnabled(true);
    }
    clearMapNum();
}
void MainWindow::clearMapNum(){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            _cirCleMapNum[i][j] = 0;
            _crossMapNum[i][j] = 0;
            board[i][j] = 0;
            tempBoard[i][j] = 0;
        }
    }
    currentDepth = 9;
}
// 判断输赢
int MainWindow::a_isWin() {//返回1电脑赢
        // 判断横向输赢
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] + board[i][1] + board[i][2] == 3)
                return 1;
            else if (board[i][0] + board[i][1] + board[i][2] == -3)
                return -1;
        }
        // 判断竖向输赢
        for (int j = 0; j < 3; j++)
        {
            if (board[0][j] + board[1][j] + board[2][j] == 3)
                return 1;
            else if (board[0][j] + board[1][j] + board[2][j] == -3)
                return -1;
        }
        // 判断斜向输赢
        if (board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3)
            return 1;
        else if (board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3)
            return -1;
        else  return 0;

}

// 人机对战的平局
bool MainWindow::a_isDraw()
{
    int times = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != 0) {
                times ++;
            }
        }
    }
    // 平局
    if (times == 9) {
        QMessageBox::information(this, tr("井字棋"), tr("平局！"), QMessageBox::Ok);
        ending();
        return true;
    }
    else
    {
        return false;
    }
}
int MainWindow::Evaluation()//电脑想赢应该让返回数值大
{
    //棋盘上1为电脑下的，0为空，-1为人下的
    //人赢了返回最小值
    if(a_isWin()==MAN){
        return -1000;
    }
    //计算机赢了返回最大值
    if(a_isWin()==COM){
        return 1000;
    }
    int count=0;//评估函数的值
    //把空的位置填满为人下的
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++) {
            if(board[i][j]==0){
                tempBoard[i][j]=MAN;
            }
            else tempBoard[i][j]=board[i][j];
        }
    }
    //计算列上有几个连成3个
    for(int i=0;i<3;i++)
        count+=(tempBoard[i][0]+tempBoard[i][1]+tempBoard[i][2])/3;
    //计算行上有几个连成3个
    for(int i=0;i<3;i++)
         count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
    //计算对角线上
    count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
    count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;
    //把空的位置填满计算机下的
    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++) {
            if (board[i][j] == 0)
                tempBoard[i][j] = COM;
            else tempBoard[i][j] = board[i][j];
        }
    }
    //计算每一行中有多少行的棋子连成3个的
    for (int i = 0; i < 3; i++)
        count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
    for (int i = 0; i < 3; i++)
        count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
    count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
    count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;

    // 返回的数因为包括了负数和整数，所以不会太大
    return count;
}

int MainWindow::AlphaBeta(int alpha,int beta,int depth){
    //估值
    int value;
    //最好位置的值
    int bestValue=0;
    //保存还可以下几步棋
    int moveCount=0;
    //保存可以下棋子的位置
    Move moveList[9];

    // 如果在深度未耗尽之前赢了
    if (a_isWin() == COM || a_isWin() == MAN)
    {
        // 这里返回的评估函数值是给递归用的
        return Evaluation();
    }
    //如果搜索深度耗尽
    if (depth == 0)
    {
        // 这里返回的评估函数值是给递归用的
        //if(Evaluation()<beta)
         //   beta=Evaluation();
        int i=Evaluation();
        return i;
    }
    //如果没赢也没耗尽深度，// 先给一个初始值
    if (COM == player) {
        bestValue = -1000;
    }
    else if (MAN == player)
    {
        bestValue = 1000;
    }
    //获取棋盘中一个空位置下子：

    moveCount=a_getMoveList(moveList);
    //可走步数为0则返回最佳
    if(moveCount < 1)
    {
        bestMove = moveList[0];
        return bestValue;
    }
    for(int i=0;i<moveCount;i++){
        //获取一个空位置
        Move curMove=moveList[i];
        //下个棋子
        a_makeMove(curMove);
        //下完子后递归调用函数

        value=AlphaBeta(alpha,beta,depth-1);
        count1++;
        //清空假装下子的位置
        a_unMakeMove(curMove);
        if(player==COM){
            if(value>bestValue){
                bestValue=value;

            }
            if(bestValue>alpha){

                if(depth==2)
                    bestMove=curMove;
                alpha=bestValue;
            }
            if(alpha>=beta){
                return alpha;
            }
        }
        else{
            if(value<bestValue){
                bestValue=value;

            }
            if(bestValue<beta){

                beta=bestValue;
            }
            if(alpha>=beta)
                return beta;
        }

    }
    return bestValue;

}
void MainWindow::a_makeMove(Move curMove) {//假装下一步棋
    board[curMove.x][curMove.y] = player;
    player = (player == COM) ? MAN : COM;
}

void MainWindow::a_unMakeMove(Move curMove) {//取消假装下的棋
    board[curMove.x][curMove.y] = 0;
    player = (player == COM) ? MAN : COM;
}
int MainWindow::a_zz_play(){
    //找当前棋盘中第一个空位置

    for(int i=0;i<3;i++){
        for (int j=0;j<3;j++) {
            if(board[j][i]==0){
                board[j][i]=MAN;
                int place = (j * 3) + i;
                for (int x = 0; x< btnList.size(); x++) {
                    if (x == place) {
                        btnList[x]->setStyleSheet("border-image: url(:/ring.png);");
                        btnList[x]->setEnabled(false);
                    }
                }
                return 1;
            }
        }
    }

}
int MainWindow::a_man_play(QPushButton *btn) {
    // 人类没有下子
    if(!btn)
        return -1;

    int x = btn->pos().x() / 100;
    int y = btn->pos().y() / 100;
    board[y][x] = MAN;
    btn->setStyleSheet("border-image: url(:/ring.png);");
    btn->setEnabled(false);


    // 普通下子
    return 1;
}
// 获取棋盘上一共还剩多少步
int MainWindow::a_getMoveList(Move moveList[]) {
    int moveCount = 0;
    int i, j;
    for (i = 0; i <3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (board[i][j] == 0)
            {
                moveList[moveCount].x = i;
                moveList[moveCount].y = j;
                moveCount++;
            }
        }
    }
    //返回一共多少个空的位置
    return moveCount;
}

int MainWindow::on_pushButton_clicked()
{
    //找当前可下棋子且能下完之后连成两个或三个的位置
    if(firstmover==1&&sx1==false){
        //人工智障先下
        sx1=true;
        qsrand(time(NULL));
        int x=qrand()%3;
        int y;
        if(x==0)
            y=x+2;
        else if(x==1)
            y=x-1;
        else y=x-1;
        board[y][x]=MAN;
        int place = (x * 3) + y;
        for (int i = 0; i < btnList.size(); i++) {
            if (i == place) {
                btnList[i]->setStyleSheet("border-image: url(:/ring.png);");
                btnList[i]->setEnabled(false);
            }
        }
        player=COM;
        a_com_play();
        currentDepth--;
        player=MAN;
        ComVSCom();
    }
    if(firstmover==0&&sx2==false){
        //人工智能先下
        sx2=true;
        a_com_play();
        currentDepth--;
        player=MAN;

    }
    else {
        ComVSCom();
    }

}
