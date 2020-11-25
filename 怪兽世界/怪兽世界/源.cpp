#include "��ͷ.h"
int score = 0;
struct coord road[100] ;
int road_count = 0;
int main(int argc, char *argv[]) {
	int realWorld[NOCOLS][NOROWS];	//������ʵ���������
	int agentWorld[NOCOLS][NOROWS];	// ����agent���������
	int x, y;						// ����
	struct coord currentCoord;		// ��ǰλ������
	struct coord start = { 0, 0 };	// ��ʼ������
	// ��ʼ��ʱ������
	srand((unsigned int)time(0));
	// ��ʼ���������綼Ϊ0
	for (y = 0; y < NOROWS; y++) {
		for (x = 0; x < NOCOLS; x++) {
			realWorld[x][y] = 0;
			agentWorld[x][y] = 0;
		}
	}
	// ����realWorld.
	generateRealWorld(realWorld);
	//���� agentWorld
	setFlag(agentWorld, start, CURRENT);	// ��ʼ����(0,0)
	// ���õ�ǰ����
	currentCoord = start;

	// ��ʾ��ʵ����
	puts("��ʵ����");
	displayWorldAll(realWorld);
	int count = 0;
	while (1) 
	{
		printf("\n============================================================\n");
		count++;
		// ���µ�ǰ����
		currentCoord = getCurrentCoord(agentWorld);
		// �����ǰ����δ���ʹ���������������
		if (testFlag(agentWorld, currentCoord, VISITED) == 0) {

			// �������������´��������ͼ
			copyFlags(realWorld, agentWorld, currentCoord);

			//����Ǻڶ����ǹ�������Ϸ�����ˣ���������
			if (testFlag(agentWorld, currentCoord, CAVE)) {
				
				printf("\nA G E N T  �� �� (Step %d)\n", count);
				printf("��ǰ����(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score -= 1000;
				cout<<"\n�����ڶ���. GAME OVER!"<<endl;
				cout << "���յ÷�" << score << endl;
				break;
			}
			else if (testFlag(agentWorld, currentCoord, WUMPUS)) {
			
				printf("\nA G E N T  ��  �� (Step %d)\n", count);
				printf("��ǰ����(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score -= 1000;
				puts("\n�����޳Ե���. GAME OVER!\n");
				cout << "���յ÷�" << score << endl;
				break;
			}
			else if (testFlag(agentWorld, currentCoord, GLOW)) {
				
				printf("\nA G E N T �� �� (Step %d)\n", count);
				printf("��ǰ����(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score += 1000;
				puts("\nʤ����! ���ҵ��˽���! ��˹!\n");
				cout << "��ǰ�÷�" << score << endl;
				struct coord temp=currentCoord;
				for (int i = road_count-1; i >= 0; i--) {
					delFlag(agentWorld, temp, CURRENT);
					setFlag(agentWorld, road[i], CURRENT);
					printf("\nA G E N T �� �� (Step %d)\n", count);
					printf("��ǰ����(%d,%d):\n", temp.x, temp.y);
					displayWorldAll(agentWorld);
					score--;
					cout << "��ǰ�÷֣�" << score << endl;
					temp = road[i];
					Sleep(150);
				}
				delFlag(agentWorld, temp, CURRENT);
				temp.x = 0;
				temp.y = 0;
				setFlag(agentWorld, temp, CURRENT);
				printf("\nA G E N T �� �� (Step %d)\n", count);
				printf("��ǰ����(%d,%d):\n", currentCoord.x, currentCoord.y);
				displayWorldAll(agentWorld);
				score--;
				cout << "���յ÷֣�" << score << endl;
				
				break;
			}
			else {
				// ����ǰ������Ϊ�ѷ��ʲ��Ƴ���ȫ���
				setFlag(agentWorld, currentCoord, VISITED);

				//�����ھӱ�ǲ�����
				evaluateNeighbors(agentWorld, currentCoord);
			}
		}
		printf("\nA G E N T  �� �� (Step %d)\n", count);
		printf("��ǰ���� (%d,%d):\n", currentCoord.x, currentCoord.y);
		displayWorldAll(agentWorld);

		if (takeGlowAction(agentWorld, currentCoord)) {
			printf("���Ǹ����ҽ��ӷ��ƶ���!\n");
		}
		else if (takeSafeAction(agentWorld, currentCoord)) {
			printf("���Ǹ��ݱ��ְ�ȫ���ƶ���!\n");
		}
		else if (takeRollTheDiceAction(agentWorld, currentCoord)) {
			printf("���Ǹ���������ƶ���!\n");
		}
		else if (takeSuicideAction(agentWorld, currentCoord)) {
			printf("���Ǹ�����ɱ���ƶ���!\n");
		}

		
		system("pause");
	}

	system("pause");
	return EXIT_SUCCESS;
}

// ���ص�ǰagent����
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
	printf("\n˵����\n����(W), �ڶ� (C),��� (G), ����Ԥ���(w), �ڶ�Ԥ��� (s), ���Ԥ�⴦(g),\n ΢�� (B), ��ζ (T), ���⴦(L), �ѷ��� (V), ��ȫ�� (S), ��ǰλ�� (A)\n\n");
	fflush(stdout);
}

void displayWorldSymbols(int world[NOROWS][NOCOLS]) {
	int x, y;
	//һ��16������ÿ�����������12��״̬��ͨ���������Գ�ÿ������ı��
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
// ��ȡ�����ֶ�����
void neighborFieldsCoords(struct coord field, struct coord results[4]) {
	// ����
	results[0].x = field.x;
	results[0].y = field.y + 1;

	// ����
	results[1].x = field.x + 1;
	results[1].y = field.y;

	// ����
	results[2].x = field.x;
	results[2].y = field.y - 1;

	// ����
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

//��һ�����縴��һ������ı�ʶ����һ��
void copyFlags(int fromWorld[NOCOLS][NOROWS], int toWorld[NOCOLS][NOROWS], struct coord field) {
	if (field.x < 0 || field.y < 0) {
		printf("Copy flag: Negative numbers!\n");
		exit(EXIT_FAILURE);
	}
	toWorld[field.x][field.y] |= fromWorld[field.x][field.y];
}

//���Է���ı�ʶ
int testFlag(int world[NOCOLS][NOROWS], struct coord field, int action) {
	if (((world[field.x][field.y] & action) == action)) {
		return 1;
	}
	else {
		return 0;
	}
}

// Ϊ�������ñ�ʶ
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

//���ɽ���min��max֮��������������except������Ԫ����ͬʱ��������

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
//�������һ������min(x,y)��max(x,y)֮���ȥexcept����������ԣ��浽����ṹ����

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

// ������ʵ������
void generateRealWorld(int realWorld[NOCOLS][NOROWS]) {
	int k, z, w;			//����
	struct coord xy;
	struct coord cavePos[NOCAVES];	// �ڶ�����
	struct coord wumpusPos[NOWUMPUS]; // ��������
	struct coord glowPos[NOGLOW];		// ��������
	struct coord neighbors[4];		

	struct coord min = { 1,1 };					// ��С�������
	struct coord max = { NOROWS - 1, NOCOLS - 1 };	//����������
	struct coord default_except = { 0,0 };		

	int except_i;		
	int except_size;	

	struct coord *except = NULL;		
	struct coord *except_temp = NULL;	

	/* ��ʼ�����ΪĬ�ϵ�except����� */
	except_i = 0;
	except_size = 1;
	if ((except = (struct coord*)calloc(except_size, sizeof(struct coord))) == NULL) {
		fprintf(stderr, "Error allocating memory.\n");
		exit(EXIT_FAILURE);
	}

	//���ò��ù��޺ͺڶ� �ڳ�����
	except[except_i] = default_except;

	// ���ɺڶ�����
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
		
		//���ɷ��񲢴浽cavePos
		cavePos[k] = randPair(min, max, except, except_i);

		//�����ɵ�randPair���except�б��У������ֶα��Ϊ��ʹ��
		except[except_i] = cavePos[k];
		k++;
	}

	// ���ɹ�������
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

	// ���ɽ�������
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

	// ��ʼ����ʵ����
	for (xy.x = 0; xy.x < NOROWS; xy.x++) {
		for (xy.y = 0; xy.y < NOCOLS; xy.y++) {

			
			for (k = 0; k < NOCAVES; k++) {
				if (xy.x == cavePos[k].x && xy.y == cavePos[k].y) {
					setFlag(realWorld, cavePos[k], CAVE);

					
					neighborFieldsCoords(xy, neighbors);

					for (z = 0; z < 4; z++) {
						/* ���÷紵���ذ������ */
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

	// ��ʾ��ʼ��Ϣ
	for (w = 0; w < NOCAVES; w++) {
		printf("%d. �ڶ�����: (%d, %d)\n", w, cavePos[w].x, cavePos[w].y);
	}

	for (w = 0; w < NOWUMPUS; w++) {
		printf("%d. ��������: (%d, %d)\n", w, wumpusPos[w].x, wumpusPos[w].y);
	}
	for (w = 0; w < NOGLOW; w++) {
		printf("%d. ��������: (%d, %d)\n", w, glowPos[w].x, glowPos[w].y);
	}
	printf("\n");
}
//
//��ȡ���������Ҹ���KB 

void evaluateNeighbors(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int z;
	struct coord neighbors[4];		// �ھ�����
	// ��ȡ�ھӵ�����
	neighborFieldsCoords(field, neighbors);
	//���������ĸ��ھ������ÿ��ɱ�־������ھӰ�ȫ���ѷ�������ԣ�
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
			//��ǰ�����з磬�����ܴ����ж���ǣ�����ھ��Ѿ������ж�������ھӱ��Ϊ��Ѩ
			
			if (testFlag(agentWorld, field, BREEZE)) {
				if (testFlag(agentWorld, neighbors[z], CAVESUS)) {
					
					//�ڶ�һ��������Ϊ֮ǰ�Ѿ��������˿����ж��ı��
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

			//�����λ��û���ṩ���������ݣ��������ܱ��Ϊ��ȫ
			if ((testFlag(agentWorld, field, BREEZE) == 0) &&
				(testFlag(agentWorld, field, STENCH) == 0)) {
				setFlag(agentWorld, neighbors[z], SAFE);

				// ɾ�����в���Ҫ�ı��
				delFlag(agentWorld, neighbors[z], CAVESUS);
				delFlag(agentWorld, neighbors[z], WUMPUSSUS);
				delFlag(agentWorld, neighbors[z], CAVE);
				delFlag(agentWorld, neighbors[z], WUMPUS);
			}

		}
	}
}

// �ƶ�
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
		printf("�����ƶ�!\n");
		cout << "��ǰ�÷֣�" << score+1 << endl;
		
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
		printf("�����ƶ�!\n");
		cout << "��ǰ�÷֣�" << score+1 << endl;
		
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
		
		printf("�����ƶ�!\n");
		cout << "��ǰ�÷֣�" << score+1 << endl;
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
		
		printf("�����ƶ�!\n");
		cout << "��ǰ�÷֣�" << score+1 << endl;
		break;
	}
}

// ��������ľ���
double calcDistance(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField) {
	double distance;
	distance = sqrt((double)pow((double)destField.x - srcField.x, 2) + (double)pow((double)destField.y - srcField.y, 2));
	return distance;
}

// �����srcField to destField�ķ���
int calcDirrection(int agentWorld[NOCOLS][NOROWS], struct coord srcField, struct coord destField) {
	int z, i, shortestGoodNeighbor;
	double shortestDist;
	struct coord neighbors[4];
	int goodNeighbors_i;				/* except������±� */
	int goodNeighbors_size;			/* ����except������±�  */

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

// Ѱ�ҽ��ӣ��ҵ�������
int takeGlowAction(int agentWorld[NOCOLS][NOROWS], struct coord field) {
	int z;
	struct coord neighbors[4];		
	// ��ȡ�ھ�����
	neighborFieldsCoords(field, neighbors);
	//������ڵķ����ǽ��ӻ��������ƽ��ӣ�ץ����
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
			printf("���ӿ����ڸ�����������ץס����!\n");
			moveOneField(agentWorld, z, field);
			return(1);
		}
	}
	return(0);
}
//ȥ����İ�ȫ��������κ�һ����ȫ�ķ��������agent����

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
	//��Ѱ���ھӷ������ǰ�ȫ��
	
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
		//�ھ���û�а�ȫ�ķ�����������������Ѱ�Ұ�ȫ
		free(exceptSF);
		int x, y, direction;
		struct coord nearestSafeFieldCoord = { -1, -1 };

		/*������һ��������Ŀǰλ������İ�ȫλ�� */
		for (x = 0; x < NOROWS; x++) {
			for (y = 0; y < NOCOLS; y++) {
				struct coord testSafeFieldCoord = { x, y };
				
				if (testFlag(agentWorld, testSafeFieldCoord, SAFE)) {
					
					if ((nearestSafeFieldCoord.x == -1) && (nearestSafeFieldCoord.y == -1)) {
						nearestSafeFieldCoord = testSafeFieldCoord;
					}
					else {
						//����ⲻ�ǵ�һ����ȫ�������Ǽ��һ�����ǲ��������һ��
						if (calcDistance(agentWorld, field, testSafeFieldCoord) < calcDistance(agentWorld, field, nearestSafeFieldCoord)) {
							nearestSafeFieldCoord = testSafeFieldCoord;
						}
					}
				}
			}
		}

		// û��ȫ������0
		if ((nearestSafeFieldCoord.x == -1) && (nearestSafeFieldCoord.y == -1)) {
			return(0);
		}
		else {
			// ��ȡ����İ�ȫ������
			direction = calcDirrection(agentWorld, field, nearestSafeFieldCoord);
			moveOneField(agentWorld, direction, field);
			return(1);
		}

	}
}

// ���ѡ��һ��·���û�а�ȫ��
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

// �Ĳ���Ч��Ϊ�˱�������ֲ�����ֻ�ܲ�ȡ��ɱ��
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

		printf("��ɱ�ɣ�good luck!\n");
		moveOneField(agentWorld, random, field);
		free(exceptRND);
		return(1);
	}
	else {
		free(exceptRND);
		return(0);
	}
}