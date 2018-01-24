#ifdef MAIN
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 10
#define MAGICNUMBER 65
#define POPAL '#'
#define PROMAX '*'
#define PYSTO '0'

enum MEM {
  MEM_VOID,
  MEM_POINT,
  MEM_DIRECTION
};

enum DIR {
  DIR_HORIZONTAL = 1,
  DIR_VERTICAL = 2
};

enum SIDE {
  SIDE_PLAYER = 1,
  SIDE_ENEMY = 2
};

char PlayerField[SIZE][SIZE];
char PlayerShotsField[SIZE][SIZE];
char EnemyField[SIZE][SIZE];
int PlayerKillSmallSeparators[4][2];
int PlayerKillSeparatorsX[6][2];
int PlayerKillSeparatorsY[6][2];
int EnemyKillSmallSeparators[4][2];
int EnemyKillSeparatorsX[6][2];
int EnemyKillSeparatorsY[6][2];
int PlayerHP = 20;
int EnemyHP = 20;
int XMem = 0;
int YMem = 0;
int WinFlag = 0;
int XodBot = 0;
enum MEM Memory = MEM_VOID;
enum DIR DirMem;

int HealthPlayerShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int HealthEnemyShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int LenShips[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
char Alp[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

int CheckEdge(int X, int Y);
void CheckShotSeparator(char Field[SIZE][SIZE], int X, int Y);
void SetKillSeparators(int NumShip, enum SIDE Side);
int InputShotCoordinate();
int ConsequencesShot(int X, int Y);
int GenerateShotCoordinate();
int DirShotCoordinate(int X, int Y);
int DirFindShotCoordintare();
int FinishShotCoordinate(int X, int Y);
int FindFinishShotCoordinate();

int RandomArray(int Array[SIZE]);
void FillField(char Field[SIZE][SIZE]);
void OutPutField(char FirstField[SIZE][SIZE], char SecondField[SIZE][SIZE]);
void SetSeparator(char Field[SIZE][SIZE], int X, int Y);
void CheckSeparator(char Field[SIZE][SIZE], int X, int Y);
int SetHorizontalShip(char Field[SIZE][SIZE], int X, int Y, int NumShip, int Side);
int SetVerticalShip(char Field[SIZE][SIZE], int X, int Y, int NumShip, int Side);
void SetBigShip(char Field[SIZE][SIZE], int NumShip);
void SetSmallShip(char Field[SIZE][SIZE],int NumShip);
void GenerateBigShip(char Field[SIZE][SIZE], int NumShip);
void GenerateSmallShip(char Field[SIZE][SIZE],int NumShip);
void ClearSeparators(char Field[SIZE][SIZE]);
void poo(char Field[SIZE][SIZE]);
void eoo(char Field[SIZE][SIZE]);
void LocationShip();
#endif
