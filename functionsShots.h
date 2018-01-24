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

extern char PlayerField[SIZE][SIZE];
extern char PlayerShotsField[SIZE][SIZE];
extern char EnemyField[SIZE][SIZE];
extern int PlayerKillSmallSeparators[4][2];
extern int PlayerKillSeparatorsX[6][2];
extern int PlayerKillSeparatorsY[6][2];
extern int EnemyKillSmallSeparators[4][2];
extern int EnemyKillSeparatorsX[6][2];
extern int EnemyKillSeparatorsY[6][2];
extern int PlayerHP;
extern int EnemyHP;
extern enum MEM Memory;
extern int DirMem;
extern int XMem;
extern int YMem;
extern int XodBot;

int HealthPlayerShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int HealthEnemyShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

void SetSeparator(char Field[SIZE][SIZE], int X, int Y);
void OutPutField(char FirstField[SIZE][SIZE], char SecondField[SIZE][SIZE]);
int RandomArray(int Array[SIZE]);

int CheckEdge(int X, int Y) {
   return ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE));
}

void CheckShotSeparator(char Field[SIZE][SIZE], int X, int Y) {
  for(int i = X - 1; i <= X + 1; i += 2) {
    for(int j = Y - 1; j <= Y + 1; j += 2) {
    SetSeparator(Field, i, j);
    }
  }
}

void SetKillSeparators(int NumShip, enum SIDE Side) {
  if (Side == SIDE_PLAYER) {
    if (NumShip < 6) {
      int X1 = EnemyKillSeparatorsX[NumShip][0];
      int X2 = EnemyKillSeparatorsX[NumShip][1];
      int Y1 = EnemyKillSeparatorsY[NumShip][0];
      int Y2 = EnemyKillSeparatorsY[NumShip][1];
      if (CheckEdge(X1, Y1)) {
        PlayerShotsField[X1][Y1] = PROMAX;
      }
      if (CheckEdge(X2, Y2)) {
        PlayerShotsField[X2][Y2] = PROMAX;
      }
    }
    else {
      int X = EnemyKillSmallSeparators[NumShip - 6][0];
      int Y = EnemyKillSmallSeparators[NumShip - 6][1];
      if (CheckEdge(X - 1, Y)) {
        PlayerShotsField[X - 1][Y] = PROMAX;
      }
      if (CheckEdge(X + 1, Y)) {
        PlayerShotsField[X + 1][Y] = PROMAX;
      }
      if (CheckEdge(X, Y - 1)) {
        PlayerShotsField[X][Y - 1] = PROMAX;
      }
      if (CheckEdge(X, Y + 1)) {
        PlayerShotsField[X][Y + 1] = PROMAX;
      }
    }
  }
  if (Side == SIDE_ENEMY) {
    if (NumShip < 6) {
      int X1 = PlayerKillSeparatorsX[NumShip][0];
      int X2 = PlayerKillSeparatorsX[NumShip][1];
      int Y1 = PlayerKillSeparatorsY[NumShip][0];
      int Y2 = PlayerKillSeparatorsY[NumShip][1];
      if (CheckEdge(X1, Y1)) {
        PlayerField[X1][Y1] = PROMAX;
      }
      if (CheckEdge(X2, Y2)) {
        PlayerField[X2][Y2] = PROMAX;
      }
    }
    else {
      int X = PlayerKillSmallSeparators[NumShip - 6][0];
      int Y = PlayerKillSmallSeparators[NumShip - 6][1];
      if (CheckEdge(X - 1, Y)) {
        PlayerField[X - 1][Y] = PROMAX;
      }
      if (CheckEdge(X + 1, Y)) {
        PlayerField[X + 1][Y] = PROMAX;
      }
      if (CheckEdge(X, Y - 1)) {
        PlayerField[X][Y - 1] = PROMAX;
      }
      if (CheckEdge(X, Y + 1)) {
        PlayerField[X][Y + 1] = PROMAX;
      }
    }
  }
}

int InputShotCoordinate() {
  int X, Y, Status = 1;
  char charY;
  while (Status == 1) {
    printf("\nInput coordinate of the shot: " );
    scanf("%1c%1d", &charY, &X);
    fflush(stdin);
    Y = (int)charY - 97;
    if (CheckEdge(X, Y) && (PlayerShotsField[X][Y] != POPAL) && (PlayerShotsField[X][Y] != PROMAX)) {
      if (EnemyField[X][Y] != PYSTO) {
        PlayerShotsField[X][Y] = POPAL;
        CheckShotSeparator(PlayerShotsField, X, Y);
        int NumShip = (int)EnemyField[X][Y] - MAGICNUMBER;
        HealthEnemyShip[NumShip] -= 1;
        EnemyHP -= 1;
        if (EnemyHP == 0) return 1;
        if (HealthEnemyShip[NumShip] == 0) {
          SetKillSeparators(NumShip, SIDE_PLAYER);
        }
      }
      else {
        PlayerShotsField[X][Y] = PROMAX;
        Status = 0;
      }
      OutPutField(PlayerField, PlayerShotsField);
    }
    else {
      OutPutField(PlayerField, PlayerShotsField);
      printf("\nError. Try again.\n");
    }
  }
  return 0;
}

int ConsequencesShot(int X, int Y) {
  XodBot = 1;
  int NumShip = (int)PlayerField[X][Y] - MAGICNUMBER;
  HealthPlayerShip[NumShip] -= 1;
  PlayerHP -= 1;
  PlayerField[X][Y] = POPAL;
  CheckShotSeparator(PlayerField, X, Y);
  if (HealthPlayerShip[NumShip] == 0) {
    SetKillSeparators(NumShip, SIDE_ENEMY);
    Memory = MEM_VOID;
  }
  if (PlayerHP == 0) return 2;
  return 0;
}

int GenerateShotCoordinate() {
  int Y, X, Status = 1, Array[SIZE], i = SIZE;
  while (Status == 1) {
    i++;
    if (i >= SIZE) {
      RandomArray(Array);
      i = 1;
    }
    X = Array[i];
    Y = Array[i - 1];
    if (PlayerField[X][Y] == PROMAX || PlayerField[X][Y] == POPAL) {
      continue;
    }
    else {
      Status = 0;
      if (PlayerField[X][Y] != PYSTO) {
        Memory = MEM_POINT;
        XMem = X;
        YMem = Y;
        if (ConsequencesShot(X, Y) == 2) return 2;
      }
      else {
        PlayerField[X][Y] = PROMAX;
        XodBot = 0;
      }
    }
  }
  return 0;
}

int DirShotCoordinate(int X, int Y) {
  if (CheckEdge(X, Y)) {
    if (PlayerField[X][Y] != PROMAX) {
      if (PlayerField[X][Y] != PYSTO) {
        Memory = MEM_DIRECTION;
        if (ConsequencesShot(X, Y) == 2) return 2;
        return 3;
      }
      else {
        PlayerField[X][Y] = PROMAX;
        XodBot = 0;
        return 0;
      }
    }
  }
  return 1;
}

int DirFindShotCoordintare() {
  int Status = 1;
  if (Status == 1) {
    Status = DirShotCoordinate(XMem - 1, YMem);
  }
  if (Status == 1) {
    Status = DirShotCoordinate(XMem + 1, YMem);
  }
  if (Status == 3) {
    DirMem = 1;
  }
  if (Status == 1) {
    Status = DirShotCoordinate(XMem, YMem - 1);
  }
  if (Status == 1) {
    Status = DirShotCoordinate(XMem, YMem + 1);
  }
  if (Status == 3) {
    DirMem = 2;
  }
  if (Status == 2) return 2;
  if (Status == 0 || Status == 3) return 0;
}

int FinishShotCoordinate(int X, int Y) {
  if (PlayerField[X][Y] != POPAL) {
    if (PlayerField[X][Y] != PYSTO) {
      if (ConsequencesShot(X, Y) == 2) return 2;
      return 0;
    }
    else {
      PlayerField[X][Y] = PROMAX;
      XodBot = 0;
      return 0;
    }
  }
  return 1;
}

int FindFinishShotCoordinate() {
  int X = XMem, Y = YMem, Status = 1;
  if (DirMem == 1) {
    while (CheckEdge(X - 1, Y) && Status == 1) {
     if (PlayerField[X - 1][Y] == PROMAX) break;
      X--;
      Status = FinishShotCoordinate(X, Y);
    }
    X = XMem;
    while (CheckEdge(X + 1, Y) && Status == 1) {
      if (PlayerField[X + 1][Y] == PROMAX) break;
      X++;
      Status = FinishShotCoordinate(X, Y);
    }
  }
  else if (DirMem == 2) {
    while (CheckEdge(X, Y - 1) && Status == 1) {
      if (PlayerField[X][Y - 1] == PROMAX) break;
      Y--;
      Status = FinishShotCoordinate(X, Y);
    }
    Y = YMem;
    while (CheckEdge(X, Y + 1) && Status == 1) {
      if (PlayerField[X][Y + 1] == PROMAX) break;
      Y++;
      Status = FinishShotCoordinate(X, Y);
    }
  }
  if (Status == 2) return 2;
  return 0;
}
