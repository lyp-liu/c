#include "标头.h"
int score = 0;
struct coord road[100] ;
int road_count = 0;
int main(int argc, char *argv[]) {
	int realWorld[NOCOLS][NOROWS];	//保存真实世界的数组
	int agentWorld[NOCOLS][NOROWS];	// 保存agent世界的数组
	int x, y;						// 计数
	struct coord currentCoord;		// 当前位置坐标
	struct coord start = { 0, 0 };	// 开始的坐标
	// 初始化时间种子
	srand((unsigned int)time(0));
	// 初始化两个世界都为0
	for (y = 0; y < NOROWS; y++) {
		for (x = 0; x < NOCOLS; x++) {
			realWorld[x][y] = 0;
			agentWorld[x][y] = 0;
		}
	}
	// 生成realWorld.
	generateRealWorld(realWorld);
	//生成 agentWorld
	setFlag(agentWorld, start, CURRENT);	// 初始点在(0,0)
	// 设置当前坐标
	currentCoord = start;

	// 显示现实世界
	puts("现实世界");
	displayWorldAll(realWorld);
	int count = 0;
	while (1) 
	{
		printf("\n============================================================\n");
		count++;
		// 更新当前坐标
		currentCoord = getCurrentCoord(agentWorld);
		// 如果当前区域未访问过，处理传感器数据
		if (testFlag(agentWorld, currentCoord, VISITED) == 0) {

			// 读传感器并更新代理世界地图
			copyFlags(realWorld, agentWorld, currentCoord);

			//检查是黑洞还是怪物，如果游戏结束了，处理传感器
			if (testFlag(agentWorld, currentCoord, CAVE)) {
				
				printf("\nA G E N T  世 界 (Step %d)\n", count);
				printf("当前坐标(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score -= 1000;
				cout<<"\n掉进黑洞了. GAME OVER!"<<endl;
				cout << "最终得分" << score << endl;
				break;
			}
			else if (testFlag(agentWorld, currentCoord, WUMPUS)) {
			
				printf("\nA G E N T  世  界 (Step %d)\n", count);
				printf("当前坐标(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score -= 1000;
				puts("\n被怪兽吃掉了. GAME OVER!\n");
				cout << "最终得分" << score << endl;
				break;
			}
			else if (testFlag(agentWorld, currentCoord, GLOW)) {
				
				printf("\nA G E N T 世 界 (Step %d)\n", count);
				printf("当前坐标(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score += 1000;
				puts("\n胜利了! 你找到了金子! 奈斯!\n");
				cout << "当前得分" << score << endl;
				struct coord temp=currentCoord;
				for (int i = road_count-1; i >= 0; i--) {
					delFlag(agentWorld, temp, CURRENT);
					setFlag(agentWorld, road[i], CURRENT);
					printf("\nA G E N T 世 界 (Step %d)\n", count);
					printf("当前坐标(%d,%d):\n", temp.x, temp.y);
					displayWorldAll(agentWorld);
					score--;
					cout << "当前得分：" << score << endl;
					temp = road[i];
					Sleep(150);
				}
				delFlag(agentWorld, temp, CURRENT);
				temp.x = 0;
				temp.y = 0;
				setFlag(agentWorld, temp, CURRENT);
				printf("\nA G E N T 世 界 (Step %d)\n", count);
				printf("当前坐标(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score--;
				cout << "最终得分：" << score << endl;
				
				break;
			}
			else {
				// 将当前坐标标记为已访问并移除安全标记
				setFlag(agentWorld, currentCoord, VISITED);

				//评估邻居标记并设置
				evaluateNeighbors(agentWorld, currentCoord);
			}
		}
		printf("\nA G E N T  世 界 (Step %d)\n", count);
		printf("当前坐标 (%d,%d):\n", currentCoord.x, currentCoord.y);
		displayWorldAll(agentWorld);

		if (takeGlowAction(agentWorld, currentCoord)) {
			printf("这是根据找金子法移动的!\n");
		}
		else if (takeSafeAction(agentWorld, currentCoord)) {
			printf("这是根据保持安全法移动的!\n");
		}
		else if (takeRollTheDiceAction(agentWorld, currentCoord)) {
			printf("这是根据随机法移动的!\n");
		}
		else if (takeSuicideAction(agentWorld, currentCoord)) {
			printf("这是根据自杀法移动的!\n");
		}

		
		system("pause");
	}

	system("pause");
	return EXIT_SUCCESS;
}

// 返回当前agent坐标
struct coord getCurrentCoord(int world[NOCOLS][NOROWS]) {
	int x, y;
	struct coord currentCoord = { -1, -1 };

	for (x = 0; x < NOROWS; x++) {
		for (y = 0; y < NOCOLS; y++) {
			struct coord testCoord = { x, y };
			if (testFlag(world, testCoord, CURRENT)) {
				currentCoord = testCoord;
			}
		}
	}

	if (currentCoord.x == -1 || currentCoord.y == -1) {
		fprintf(stderr, "Something went wrong! We have managed to misplace our agent.\n");
		exit(EXIT_FAILURE);
	}
	else {
		return currentCoord;
	}
}

void displayWorldAll(int world[NOROWS][NOCOLS]) {
	
	displayWorldSymbols(world);
	printf("\n说明：\n怪兽(W), 黑洞 (C),金币 (G), 怪兽预测地(w), 黑洞预测地 (s), 金币预测处(g),\n 微风 (B), 臭味 (T), 发光处(L), 已访问 (V), 安全处 (S), 当前位置 (A)\n\n");
	fflush(stdout);
}

void displayWorldSymbols(int world[NOROWS][NOCOLS]) {
	int x, y;
	//一共16个方格，每个方格可能有12种状态，通过遍历测试出每个方格的标记
	for (y = NOROWS - 1; y >= 0; y--) {
		for (x = 0; x < NOCOLS; x++) {
			struct coord current = { x, y };
			if (testFlag(world, current, WUMPUS)) {
				printf("W");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, CAVE)) {
				printf("C");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, GLOW)) {
				printf("G");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, WUMPUSSUS)) {
				printf("w");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, CAVESUS)) {
				printf("c");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, GLOWSUS)) {
				printf("g");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, BREEZE)) {
				printf("B");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, STENCH)) {
				printf("T");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, GLOWING)) {
				printf("L");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, VISITED)) {
				printf("V");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, SAFE)) {
				printf("S");
			}
			else {
				printf("*");
			}

			if (testFlag(world, current, CURRENT)) {
				printf("A");
			}
			else {
				printf("*");
			}
			
			printf("\t");
		}
		printf("\n");
	}
}
// 获取给定字段坐标
void neighborFieldsCoords(struct coord field, struct coord results[4]) {
	// 向上
	results[0].x = field.x;
	results[0].y = field.y + 1;

	// 向左
	results[1].x = field.x + 1;
	results[1].y = field.y;

	// 向下
	results[2].x = field.x;
	results[2].y = field.y - 1;

	// 向右
	results[3].x = field.x - 1;
	results[3].y = field.y;
}

void delFlag(int world[NOCOLS][NOROWS], struct coord field, int action) {
	if (field.x < 0 || field.y < 0) {
		printf("Del flag: Negative numbers!\n");
		exit(EXIT_FAILURE);
	}
	world[field.x][field.y] = world[field.x][field.y] & ~action;
}

//从一个世界复制一个方格的标识到另一个
void copyFlags(int fromWorld[NOCOLS][NOROWS], int toWorld[NOCOLS][NOROWS], struct coord field) {
	if (field.x < 0 || field.y < 0) {
		printf("Copy flag: Negative numbers!\n");
		exit(EXIT_FAILURE);
	}
	toWorld[field.x][field.y] |= fromWorld[field.x][field.y];
}

//测试方格的标识
int testFlag(int world[NOCOLS][NOROWS], struct coord field, int action) {
	if (((world[field.x][field.y] & action) == action)) {
		return 1;
	}
	else {
		return 0;
	}
}

// 为方格设置标识
void setFlag(int world[NOCOLS][NOROWS], struct coord field, int action) {
	// TODO: REMOVE, testing only
	if (field.x < 0 || field.y < 0) {
		printf("setFlag: Negative numbers!\n");
		exit(EXIT_FAILURE);
	}
	if (action == VISITED) {
		delFlag(world, field, SAFE);
		delFlag(world, field, CAVESUS);
		delFlag(world, field, GLOWSUS);
		delFlag(world, field, WUMPUSSUS);
	}
	world[field.x][field.y] = world[field.x][field.y] | action;
}

//生成介于min和max之间的随机整数，与except数组中元素相同时重新生成

int randInt(int min, int max, int *except, int noExcept) {
	int result, i;
	//result = min + rand() / ((RAND_MAX / (max - min + 1)) + 1);
	result = rand() % (max - min + 1) + min;
	if (except != NULL) {
		for (i = 0; i < noExcept; i++) {
			if (result == except[i]) {
				result = randInt(min, max, except, noExcept);
				break;
			}
		}
	}
	return result;
}
//随机生成一个介于min(x,y)和max(x,y)之间除去except向量外的数对，存到坐标结构体中

struct coord randPair(struct coord min, struct coord max, struct coord *except, int noExcept) {
	int i;
	struct coord result;
	result.x = randInt(min.x, max.x, NULL, 0);

	result.y = randInt(min.y, max.y, NULL, 0);

	if (except != NULL) {
		for (i = 0; i < noExcept; i++) {
			if (result.x == except[i].x && result.y == except[i].y) {
				result = randPair(min, max, except, noExcept);
				break;
			}
		}
	}
	return result;
}

// 生成真实的世界
void generateRealWorld(int realWorld[NOCOLS][NOROWS]) {
	int k, z, w;			//计数
	struct coord xy;
	struct coord cavePos[NOCAVES];	// 黑洞坐标
	struct coord wumpusPos[NOWUMPUS]; // 怪首坐标
	struct coord glowPos[NOGLOW];		// 金子坐标
	struct coord neighbors[4];		

	struct coord min = { 1,1 };					// 最小随机数对
	struct coord max = { NOROWS - 1, NOCOLS - 1 };	//最大随机数对
	struct coord default_except = { 0,0 };		

	int except_i;		
	int except_size;	

	struct coord *except = NULL;		
	struct coord *except_temp = NULL;	

	/* 初始化起点为默认的except数组点 */
	except_i = 0;
	except_size = 1;
	if ((except = (struct coord*)calloc(except_size, sizeof(struct coord))) == NULL) {
		fprintf(stderr, "Error allocating memory.\n");
		exit(EXIT_FAILURE);
	}

	//设置不让怪兽和黑洞 在出生点
	except[except_i] = default_except;

	// 生成黑洞坐标
	k = 0;
	while (k < NOCAVES) {
		except_i++;		// This is new except
		if (except_i == except_size) {
			except_size += 1;	// New except size including this new except
			if ((except_temp = (struct coord*)realloc(except, except_size * sizeof(struct coord))) == NULL) {
				fprintf(stderr, "Ran out of memory while expanding except array.\n");
				free(except);
				exit(EXIT_FAILURE);
			}
			except = except_temp;	
		}
		
		//生成方格并存到cavePos
		cavePos[k] = randPair(min, max, except, except_i);

		//将生成的randPair添加except列表中，将此字段标记为已使用
		except[except_i] = cavePos[k];
		k++;
	}

	// 生成怪兽坐标
	k = 0;
	while (k < NOWUMPUS) {
		except_i++;
		if (except_i == except_size) {
			except_size += 1;
			if ((except_temp = (struct coord*)realloc(except, except_size * sizeof(struct coord))) == NULL) {
				fprintf(stderr, "Ran out of memory while expanding except array.\n");
				free(except);
				exit(EXIT_FAILURE);
			}
			except = except_temp;
		}

		wumpusPos[k] = randPair(min, max, except, except_i);

		except[except_i] = wumpusPos[k];

		k++;
	}

	// 生成金子坐标
	k = 0;
	while (k < NOGLOW) {
		except_i++;
		if (except_i == except_size) {
			except_size += 1;
			if ((except_temp = (struct coord*)realloc(except, except_size * sizeof(struct coord))) == NULL) {
				fprintf(stderr, "Ran out of memory while expanding except array.\n");
				free(except);
				exit(EXIT_FAILURE);
			}
			except = except_temp;
		}

		glowPos[k] = randPair(min, max, except, except_i);

		except[except_i] = glowPos[k];
		k++;
	}

	free(except);

	// 初始化真实世界
	for (xy.x = 0; xy.x < NOROWS; xy.x++) {
		for (xy.y = 0; xy.y < NOCOLS; xy.y++) {

			
			for (k = 0; k < NOCAVES; k++) {
				if (xy.x == cavePos[k].x && xy.y == cavePos[k].y) {
					setFlag(realWorld, cavePos[k], CAVE);

					
					neighborFieldsCoords(xy, neighbors);

					for (z = 0; z < 4; z++) {
						/* 不让风吹出地板的限制 */
						if (
							((neighbors[z].y < NOROWS) && (z == 0))
							||
							((neighbors[z].x < NOCOLS) && (z == 1))
							||
							((neighbors[z].y >= 0) && (z == 2))
							||
							((neighbors[z].x >= 0) && (z == 3))
							) {
							setFlag(realWorld, neighbors[z], BREEZE);
						}
					}
				}
			}
			for (k = 0; k < NOWUMPUS; k++) {
				if (xy.x == wumpusPos[k].x && xy.y == wumpusPos[k].y) {
					setFlag(realWorld, wumpusPos[k], WUMPUS);

					neighborFieldsCoords(xy, neighbors);

					for (z = 0; z < 4; z++) {
						if (
							((neighbors[z].y < NOROWS) && (z == 0))
							||
							((neighbors[z].x < NOCOLS) && (z == 1))
							||
							((neighbors[z].y >= 0) && (z == 2))
							||
							((neighbors[z].x >= 0) && (z == 3))
							) {
							setFlag(realWorld, neighbors[z], STENCH);
						}
					}
				}
			}
			for (k = 0; k < NOGLOW; k++) {
				if (xy.x == glowPos[k].x && xy.y == glowPos[k].y) {
					setFlag(realWorld, glowPos[k], GLOW);

					neighborFieldsCoords(xy, neighbors);

					for (z = 0; z < 4; z++) {
						if (
							((neighbors[z].y < NOROWS) && (z == 0))
							||
							((neighbors[z].x < NOCOLS) && (z == 1))
							||
							((neighbors[z].y >= 0) && (z == 2))
							||
							((neighbors[z].x >= 0) && (z == 3))
							) {
							setFlag(realWorld, neighbors[z], GLOWING);
						}
					}
				}
			}
		}
	}

	// 显示初始信息
	for (w = 0; w < NOCAVES; w++) {
		printf("%d. 黑洞坐标: (%d, %d)\n", w, cavePos[w].x, cavePos[w].y);
	}

	for (w = 0; w < NOWUMPUS; w++) {
		printf("%d. 怪兽坐标: (%d, %d)\n", w, wumpusPos[w].x, wumpusPos[w].y);
	}
	for (w = 0; w < NOGLOW; w++) {
		printf("%d. 金子坐标: (%d, %d)\n", w, glowPos[w].x, glowPos[w].y);
	}
	printf("\n");
}
//
//读取传感器并且更新KB 

void evaluateNeighbors(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int z;
	struct coord neighbors[4];		// 邻居坐标
	// 获取邻居的坐标
	neighborFieldsCoords(field, neighbors);
	//迭代所有四个邻居以设置可疑标志（如果邻居安全且已访问则忽略）
	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y < NOROWS) && (z == 0))
			||
			((neighbors[z].x < NOCOLS) && (z == 1))
			||
			((neighbors[z].y >= 0) && (z == 2))
			||
			((neighbors[z].x >= 0) && (z == 3))
			)
			&&
			(testFlag(agentWorld, neighbors[z], SAFE) == 0)
			&&
			(testFlag(agentWorld, neighbors[z], VISITED) == 0)
			) {
			//当前方格有风，在四周打上有洞标记，如果邻居已经有了有洞标记则邻居标记为洞穴
			
			if (testFlag(agentWorld, field, BREEZE)) {
				if (testFlag(agentWorld, neighbors[z], CAVESUS)) {
					
					//黑洞一定在那因为之前已经被打上了可能有洞的标记
					setFlag(agentWorld, neighbors[z], CAVE);
				}
				else {
					setFlag(agentWorld, neighbors[z], CAVESUS);
				}
			}

			if (testFlag(agentWorld, field, STENCH)) {
				if (testFlag(agentWorld, neighbors[z], WUMPUSSUS)) {
					setFlag(agentWorld, neighbors[z], WUMPUS);
				}
				else {
					setFlag(agentWorld, neighbors[z], WUMPUSSUS);
				}
			}

			if (testFlag(agentWorld, field, GLOWING)) {
				if (testFlag(agentWorld, neighbors[z], GLOWSUS)) {
					setFlag(agentWorld, neighbors[z], GLOW);
				}
				else {
					setFlag(agentWorld, neighbors[z], GLOWSUS);
				}
			}

			//如果该位置没有提供传感器数据，将其四周标记为安全
			if ((testFlag(agentWorld, field, BREEZE) == 0) &&
				(testFlag(agentWorld, field, STENCH) == 0)) {
				setFlag(agentWorld, neighbors[z], SAFE);

				// 删除所有不必要的标记
				delFlag(agentWorld, neighbors[z], CAVESUS);
				delFlag(agentWorld, neighbors[z], WUMPUSSUS);
				delFlag(agentWorld, neighbors[z], CAVE);
				delFlag(agentWorld, neighbors[z], WUMPUS);
			}

		}
	}
}

// 移动
void moveOneField(int agentWorld[NOCOLS][NOROWS], int direction, struct coord srcField) {
	struct coord temp;
	agentWorld[srcField.x][srcField.y] = agentWorld[srcField.x][srcField.y] & ~CURRENT;
	switch (direction) {
		// Up
	case 0:
		temp.x = srcField.x;
		temp.y = srcField.y + 1;
		setFlag(agentWorld, temp, CURRENT);
		if (testFlag(agentWorld, temp, VISITED)) {
			road[road_count].x = 0;
			road[road_count].y = 0;
			road_count--;
		}
		else {
			road[road_count].x = temp.x;
			road[road_count].y = temp.y;
			road_count++;
		}
		score--;
		printf("向上移动!\n");
		cout << "当前得分：" << score+1 << endl;
		
		break;
		// Right
	case 1:
		temp.x = srcField.x + 1;
		temp.y = srcField.y;
		setFlag(agentWorld, temp, CURRENT);
		if (testFlag(agentWorld, temp, VISITED)) {
			road[road_count].x = 0;
			road[road_count].y = 0;
			road_count--;
		}
		else {
			road[road_count].x = temp.x;
			road[road_count].y = temp.y;
			road_count++;
		}
		score--;
		printf("向右移动!\n");
		cout << "当前得分：" << score+1 << endl;
		
		break;
		// Down
	case 2:
		temp.x = srcField.x;
		temp.y = srcField.y - 1;
		setFlag(agentWorld, temp, CURRENT);
		if (testFlag(agentWorld, temp, VISITED)) {
			road[road_count].x = 0;
			road[road_count].y = 0;
			road_count--;
		}
		else {
			road[road_count].x = temp.x;
			road[road_count].y = temp.y;
			road_count++;
		}
		score--;
		
		printf("向下移动!\n");
		cout << "当前得分：" << score+1 << endl;
		break;
		// Left
	case 3:
		temp.x = srcField.x - 1;
		temp.y = srcField.y;
		setFlag(agentWorld, temp, CURRENT);
		if (testFlag(agentWorld, temp, VISITED)) {
			road[road_count].x = 0;
			road[road_count].y = 0;
			road_count--;
		}
		else {
			road[road_count].x = temp.x;
			road[road_count].y = temp.y;
			road_count++;
		}
		score--;
		
		printf("向左移动!\n");
		cout << "当前得分：" << score+1 << endl;
		break;
	}
}

// 计算两块的距离
double calcDistance(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField) {
	double distance;
	distance = sqrt((double)pow((double)destField.x - srcField.x, 2) + (double)pow((double)destField.y - srcField.y, 2));
	return distance;
}

// 计算从srcField to destField的方向
int calcDirrection(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField) {
	int z, i, shortestGoodNeighbor;
	double shortestDist;
	struct coord neighbors[4];
	int goodNeighbors_i;				/* except数组的下标 */
	int goodNeighbors_size;			/* 不在except数组的下标  */

	int *goodNeighbors = NULL;			
	int *goodNeighbors_temp = NULL;	

	double *distances = NULL;			/* Array with exceptions */
	double *distances_temp = NULL;	/* Intermediate for validating realloc(). */

	neighborFieldsCoords(srcField, neighbors);

	goodNeighbors_i = 0;
	goodNeighbors_size = 0;

	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y < NOROWS) && (z == 0))
			||
			((neighbors[z].x < NOCOLS) && (z == 1))
			||
			((neighbors[z].y >= 0) && (z == 2))
			||
			((neighbors[z].x >= 0) && (z == 3))
			)
			&&
			(testFlag(agentWorld, neighbors[z], VISITED))
			) {
			if (goodNeighbors_i == 0) {
				goodNeighbors_size++;
				if ((goodNeighbors = (int*)calloc(goodNeighbors_size, sizeof(int))) == NULL) {
					fprintf(stderr, "Error allocating memory.\n");
					exit(EXIT_FAILURE);
				}
				if ((distances = (double*)calloc(goodNeighbors_size, sizeof(double))) == NULL) {
					fprintf(stderr, "Error allocating memory.\n");
					exit(EXIT_FAILURE);
				}
			}
			else if (goodNeighbors_i == goodNeighbors_size) {
				goodNeighbors_size++;
				if ((goodNeighbors_temp = (int*)realloc(goodNeighbors, goodNeighbors_size * sizeof(int))) == NULL) {
					fprintf(stderr, "Ran out of memory while expanding except array.\n");
					free(goodNeighbors);
					exit(EXIT_FAILURE);
				}
				if ((distances_temp = (double*)realloc(distances, goodNeighbors_size * sizeof(double))) == NULL) {
					fprintf(stderr, "Ran out of memory while expanding except array.\n");
					free(distances);
					exit(EXIT_FAILURE);
				}
				goodNeighbors = goodNeighbors_temp;
				distances = distances_temp;
			}
			goodNeighbors[goodNeighbors_i] = z;

			distances[goodNeighbors_i] = calcDistance(agentWorld, neighbors[z], destField);
			goodNeighbors_i++;
		}
	}

	if (goodNeighbors != 0) {
		shortestGoodNeighbor = goodNeighbors[0];
		shortestDist = distances[0];
		for (i = 1; i < goodNeighbors_i; i++) {
			if (distances[i] < shortestDist) {
				shortestGoodNeighbor = goodNeighbors[i];
				shortestDist = distances[i];
			}
		}
	}
	free(goodNeighbors);
	free(distances);
	return shortestGoodNeighbor;
}

// 寻找金子，找到就拿走
int takeGlowAction(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int z;
	struct coord neighbors[4];		
	// 获取邻居坐标
	neighborFieldsCoords(field, neighbors);
	//如果相邻的方格是金子或者是疑似金子，抓起它
	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y < NOROWS) && (z == 0))
			||
			((neighbors[z].x < NOCOLS) && (z == 1))
			||
			((neighbors[z].y >= 0) && (z == 2))
			||
			((neighbors[z].x >= 0) && (z == 3))
			)
			&&
			(
				testFlag(agentWorld, neighbors[z], GLOW)
				)
			) {
			printf("金子可能在附近，让我们抓住它吧!\n");
			moveOneField(agentWorld, z, field);
			return(1);
		}
	}
	return(0);
}
//去最近的安全方格如果任何一个安全的方格存在于agent世界

int takeSafeAction(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int random, z;
	struct coord neighbors[4];		

	neighborFieldsCoords(field, neighbors);

	int except_i;				
	int except_size;			

	int *exceptSF = NULL;			/* Array with exceptions */
	int *exceptSF_temp = NULL;	/* Intermediate for validating realloc(). */

	except_i = 0;
	except_size = 0;
	//先寻找邻居方格中是安全的
	
	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y > NOROWS - 1) && (z == 0))
			||
			((neighbors[z].x > NOCOLS - 1) && (z == 1))
			||
			((neighbors[z].y < 0) && (z == 2))
			||
			((neighbors[z].x < 0) && (z == 3))
			)
			||
			(testFlag(agentWorld, neighbors[z], VISITED))
			||
			(testFlag(agentWorld, neighbors[z], SAFE) == 0)
			) {
			if (except_i == 0) {
				except_size++;
				if ((exceptSF = (int*)calloc(except_size, sizeof(int))) == NULL) {
					fprintf(stderr, "Error allocating memory.\n");
					exit(EXIT_FAILURE);
				}
			}
			else if (except_i == except_size) {
				except_size++;
				if ((exceptSF_temp = (int*)realloc(exceptSF, except_size * sizeof(int))) == NULL) {
					fprintf(stderr, "Ran out of memory while expanding except array.\n");
					free(exceptSF);
					exit(EXIT_FAILURE);
				}
				exceptSF = exceptSF_temp;
			}
			exceptSF[except_i] = z;
			except_i++;
		}
	}

	if (except_i < 4) {
		random = randInt(0, 3, exceptSF, except_i);

		moveOneField(agentWorld, random, field);
		free(exceptSF);
		return(1);
	}
	else {
		//邻居中没有安全的方格，则在整个世界中寻找安全
		free(exceptSF);
		int x, y, direction;
		struct coord nearestSafeFieldCoord = { -1, -1 };

		/*我们找一个离我们目前位置最近的安全位置 */
		for (x = 0; x < NOROWS; x++) {
			for (y = 0; y < NOCOLS; y++) {
				struct coord testSafeFieldCoord = { x, y };
				
				if (testFlag(agentWorld, testSafeFieldCoord, SAFE)) {
					
					if ((nearestSafeFieldCoord.x == -1) && (nearestSafeFieldCoord.y == -1)) {
						nearestSafeFieldCoord = testSafeFieldCoord;
					}
					else {
						//如果这不是第一个安全区域，我们检查一下它是不是最近的一个
						if (calcDistance(agentWorld, field, testSafeFieldCoord) < calcDistance(agentWorld, field, nearestSafeFieldCoord)) {
							nearestSafeFieldCoord = testSafeFieldCoord;
						}
					}
				}
			}
		}

		// 没安全区返回0
		if ((nearestSafeFieldCoord.x == -1) && (nearestSafeFieldCoord.y == -1)) {
			return(0);
		}
		else {
			// 获取最近的安全区方向
			direction = calcDirrection(agentWorld, field, nearestSafeFieldCoord);
			moveOneField(agentWorld, direction, field);
			return(1);
		}

	}
}

// 随机选下一步路如果没有安全区
int takeRollTheDiceAction(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int random, z;

	struct coord neighbors[4];
	neighborFieldsCoords(field, neighbors);

	int except_i;
	int except_size;

	int *exceptRND = NULL;
	int *exceptRND_temp = NULL;


	except_i = 0;
	except_size = 0;

	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y > NOROWS - 1) && (z == 0))
			||
			((neighbors[z].x > NOCOLS - 1) && (z == 1))
			||
			((neighbors[z].y < 0) && (z == 2))
			||
			((neighbors[z].x < 0) && (z == 3))
			)
			||
			(testFlag(agentWorld, neighbors[z], VISITED))
			||
			(testFlag(agentWorld, neighbors[z], CAVE))
			||
			(testFlag(agentWorld, neighbors[z], WUMPUS))
			) {
			if (except_i == 0) {
				except_size++;
				if ((exceptRND = (int*)calloc(except_size, sizeof(int))) == NULL) {
					fprintf(stderr, "Error allocating memory.\n");
					exit(EXIT_FAILURE);
				}
			}
			else if (except_i == except_size) {
				except_size++;
				if ((exceptRND_temp = (int*)realloc(exceptRND, except_size * sizeof(int))) == NULL) {
					fprintf(stderr, "Ran out of memory while expanding except array.\n");
					free(exceptRND);
					exit(EXIT_FAILURE);
				}
				exceptRND = exceptRND_temp;
			}
			exceptRND[except_i] = z;
			except_i++;
		}
	}

	if (except_i < 4) {
		random = randInt(0, 3, exceptRND, except_i);

		printf("Roll the dice!\n");
		moveOneField(agentWorld, random, field);
		free(exceptRND);
		return(1);
	}
	else {
		free(exceptRND);
		return(0);
	}
}

// 赌博无效，为了避免陷入局部最优只能采取自杀法
int takeSuicideAction(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int random, z;

	struct coord neighbors[4];
	neighborFieldsCoords(field, neighbors);

	int except_i;
	int except_size;

	int *exceptRND = NULL;
	int *exceptRND_temp = NULL;

	except_i = 0;
	except_size = 0;

	for (z = 0; z < 4; z++) {
		if ((
			((neighbors[z].y > NOROWS - 1) && (z == 0))
			||
			((neighbors[z].x > NOCOLS - 1) && (z == 1))
			||
			((neighbors[z].y < 0) && (z == 2))
			||
			((neighbors[z].x < 0) && (z == 3))
			)
			||
			(testFlag(agentWorld, neighbors[z], VISITED))
			) {
			if (except_i == 0) {
				except_size++;
				if ((exceptRND = (int*)calloc(except_size, sizeof(int))) == NULL) {
					fprintf(stderr, "Error allocating memory.\n");
					exit(EXIT_FAILURE);
				}
			}
			else if (except_i == except_size) {
				except_size++;
				if ((exceptRND_temp = (int*)realloc(exceptRND, except_size * sizeof(int))) == NULL) {
					fprintf(stderr, "Ran out of memory while expanding except array.\n");
					free(exceptRND);
					exit(EXIT_FAILURE);
				}
				exceptRND = exceptRND_temp;
			}
			exceptRND[except_i] = z;
			except_i++;
		}
	}

	if (except_i < 4) {
		random = randInt(0, 3, exceptRND, except_i);

		printf("自杀吧，good luck!\n");
		moveOneField(agentWorld, random, field);
		free(exceptRND);
		return(1);
	}
	else {
		free(exceptRND);
		return(0);
	}
}