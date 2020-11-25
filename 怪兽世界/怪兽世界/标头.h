#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>			//Need for srand(time(NULL))
#include <math.h>
#include<iostream>
#include<Windows.h>
using namespace std;
#define NOROWS 		4		// ����rows
#define NOCOLS 		4		// ����columns

#define NOWUMPUS 	1		// ��������
#define NOCAVES  	3		// �ڶ�����
#define NOGLOW   	1		// ������

#define NOFBITS	   	12		// Number of bits inside flag vector

#define WUMPUS      2048
#define CAVE        1024
#define GLOW        512
#define WUMPUSSUS   256
#define CAVESUS     128
#define GLOWSUS     64
#define BREEZE      32
#define STENCH      16
#define GLOWING     8
#define VISITED     4
#define SAFE 		2
#define CURRENT     1

struct coord {//����
	int x;
	int y;
};

int realWorld[NOCOLS][NOROWS];


void displayWorldSymbols(int world[NOROWS][NOCOLS]);
void displayWorldAll(int world[NOROWS][NOCOLS]);
void neighborFieldsCoords(struct coord field, struct coord results[4]);
void setFlag(int world[NOCOLS][NOROWS], struct coord field, int action);
int randInt(int min, int max, int *except, int noExcept);
struct coord randPair(struct coord min, struct coord max, struct coord *except, int noExcept);
void generateRealWorld(int realWorld[NOCOLS][NOROWS]);
void evaluateNeighbors(int agentWorld[NOCOLS][NOROWS], struct coord field);
void moveOneField(int agentWorld[NOCOLS][NOROWS], int direction, struct coord srcField);
void delFlag(int world[NOCOLS][NOROWS], struct coord field, int action);
void copyFlags(int fromWorld[NOCOLS][NOROWS], int toWorld[NOCOLS][NOROWS], struct coord field);
int testFlag(int world[NOCOLS][NOROWS], struct coord field, int action);
struct coord getCurrentCoord(int world[NOCOLS][NOROWS]);
int calcDirrection(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField);
double calcDistance(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField);
int takeGlowAction(int agentWorld[NOCOLS][NOROWS], struct coord field);
int takeSafeAction(int agentWorld[NOCOLS][NOROWS], struct coord field);
int takeRollTheDiceAction(int agentWorld[NOCOLS][NOROWS], struct coord field);
int takeSuicideAction(int agentWorld[NOCOLS][NOROWS], struct coord field);


