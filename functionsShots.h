#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define SIZE 10
#define MAGICNUMBER 65

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

int CheckEdge (int X, int Y) {
   if ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE)) {
     return true;
   }
   else {
     return false;
   }
}

void CheckShotSeparator(char Field[SIZE][SIZE], int X, int Y) {
  if (CheckEdge(X - 1, Y + 1)) {
    SetSeparator(Field, X - 1, Y + 1);
  };
  if (CheckEdge(X + 1, Y + 1)) {
    SetSeparator(Field, X + 1, Y + 1);
  };
  if (CheckEdge(X - 1, Y - 1)) {
    SetSeparator(Field, X - 1, Y - 1);
  };
  if (CheckEdge(X + 1, Y - 1)) {
    SetSeparator(Field, X + 1, Y - 1);
  };
}

void SetKillSeparators(int NumShip, int Side) {
  if (Side == 1) {
    if (NumShip < 6) {
      int X1 = EnemyKillSeparatorsX[NumShip][0];
      int X2 = EnemyKillSeparatorsX[NumShip][1];
      int Y1 = EnemyKillSeparatorsY[NumShip][0];
      int Y2 = EnemyKillSeparatorsY[NumShip][1];
      if (CheckEdge(X1, Y1)) {
        PlayerShotsField[X1][Y1] = '*';
      }
      if (CheckEdge(X2, Y2)) {
        PlayerShotsField[X2][Y2] = '*';
      }
    }
    else {
      int X = EnemyKillSmallSeparators[NumShip - 6][0];
      int Y = EnemyKillSmallSeparators[NumShip - 6][1];
      if (CheckEdge(X - 1, Y)) {
        PlayerShotsField[X - 1][Y] = '*';
      }
      if (CheckEdge(X + 1, Y)) {
        PlayerShotsField[X + 1][Y] = '*';
      }
      if (CheckEdge(X, Y - 1)) {
        PlayerShotsField[X][Y - 1] = '*';
      }
      if (CheckEdge(X, Y + 1)) {
        PlayerShotsField[X][Y + 1] = '*';
      }
    }
  }
  if (Side == 2) {
    if (NumShip < 6) {
      int X1 = PlayerKillSeparatorsX[NumShip][0];
      int X2 = PlayerKillSeparatorsX[NumShip][1];
      int Y1 = PlayerKillSeparatorsY[NumShip][0];
      int Y2 = PlayerKillSeparatorsY[NumShip][1];
      if (CheckEdge(X1, Y1)) {
        PlayerField[X1][Y1] = '*';
      }
      if (CheckEdge(X2, Y2)) {
        PlayerField[X2][Y2] = '*';
      }
    }
    else {
      int X = PlayerKillSmallSeparators[NumShip - 6][0];
      int Y = PlayerKillSmallSeparators[NumShip - 6][1];
      if (CheckEdge(X - 1, Y)) {
        PlayerField[X - 1][Y] = '*';
      }
      if (CheckEdge(X + 1, Y)) {
        PlayerField[X + 1][Y] = '*';
      }
      if (CheckEdge(X, Y - 1)) {
        PlayerField[X][Y - 1] = '*';
      }
      if (CheckEdge(X, Y + 1)) {
        PlayerField[X][Y + 1] = '*';
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
    if (CheckEdge(X, Y) && (PlayerShotsField[X][Y] != '#') && (PlayerShotsField[X][Y] != '*')) {
      if (EnemyField[X][Y] != '0') {
        PlayerShotsField[X][Y] = '#';
        CheckShotSeparator(PlayerShotsField, X, Y);
        int NumShip = (int)EnemyField[X][Y] - MAGICNUMBER;
        HealthEnemyShip[NumShip] -= 1;
        EnemyHP -= 1;
        if (EnemyHP == 0) return 1;
        if (HealthEnemyShip[NumShip] == 0) {
          SetKillSeparators(NumShip, 1);
        }
      }
      else {
        PlayerShotsField[X][Y] = '*';
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
    if (PlayerField[X][Y] == '*' || PlayerField[X][Y] == '#') {
      continue;
    }
    else {
      Status = 0;
      if (PlayerField[X][Y] != '0') {
        XodBot = 1;
        Memory = MEM_POINT;
        XMem = X;
        YMem = Y;
        int NumShip = (int)PlayerField[X][Y] - MAGICNUMBER;
        HealthPlayerShip[NumShip] -= 1;
        PlayerHP -= 1;
        if (PlayerHP == 0) return 2;
        PlayerField[X][Y] = '#';
        //OutPutField(PlayerField, EnemyField);
        CheckShotSeparator(PlayerField, X, Y);
        if (HealthPlayerShip[NumShip] == 0) {
          SetKillSeparators(NumShip, 2);
          Memory = MEM_VOID;
        }
      }
      else {
        PlayerField[X][Y] = '*';
        XodBot = 0;
      }
    }
  }
  //OutPutField(PlayerField, EnemyField);
  return 0;
}

int DirShotCoordinate(int X, int Y) {
  if (CheckEdge(X, Y)) {
    if (PlayerField[X][Y] != '*') {
      if (PlayerField[X][Y] != '0') {
        XodBot = 1;
        Memory = MEM_DIRECTION;
        int NumShip = (int)PlayerField[X][Y] - MAGICNUMBER;
        HealthPlayerShip[NumShip] -= 1;
        PlayerHP -= 1;
        if (PlayerHP == 0) return 2;
        PlayerField[X][Y] = '#';
        CheckShotSeparator(PlayerField, X, Y);
        if (HealthPlayerShip[NumShip] == 0) {
          SetKillSeparators(NumShip, 2);
          Memory = MEM_VOID;
        }
        return 3;
      }
      else {
        PlayerField[X][Y] = '*';
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
  if (PlayerField[X][Y] != '#') {
    if (PlayerField[X][Y] != '0') {
      XodBot = 1;
      int NumShip = (int)PlayerField[X][Y] - MAGICNUMBER;
      HealthPlayerShip[NumShip] -= 1;
      PlayerHP -= 1;
      if (PlayerHP == 0) return 2;
      PlayerField[X][Y] = '#';
      CheckShotSeparator(PlayerField, X, Y);
      if (HealthPlayerShip[NumShip] == 0) {
        SetKillSeparators(NumShip, 2);
        Memory = MEM_VOID;
      }
      return 0;
    }
    else {
      PlayerField[X][Y] = '*';
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
     if (PlayerField[X - 1][Y] == '*') break;
      X--;
      Status = FinishShotCoordinate(X, Y);
    }
    X = XMem;
    while (CheckEdge(X + 1, Y) && Status == 1) {
      if (PlayerField[X + 1][Y] == '*') break;
      X++;
      Status = FinishShotCoordinate(X, Y);
    }
  }
  else if (DirMem == 2) {
    while (CheckEdge(X, Y - 1) && Status == 1) {
      if (PlayerField[X][Y - 1] == '*') break;
      Y--;
      Status = FinishShotCoordinate(X, Y);
    }
    Y = YMem;
    while (CheckEdge(X, Y + 1) && Status == 1) {
      if (PlayerField[X][Y + 1] == '*') break;
      Y++;
      Status = FinishShotCoordinate(X, Y);
    }
  }
  if (Status == 2) return 2;
  return 0;
}
