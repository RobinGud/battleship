#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10

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
extern int Memory;
extern int DirMem;
extern int XMem;
extern int YMem;
extern int XodBot;

int HealthPlayerShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
int HealthEnemyShip[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

void SetSeparator(char Field[SIZE][SIZE], int X, int Y);
void OutPutField(char FirstField[SIZE][SIZE], char SecondField[SIZE][SIZE]);
int RandomArray(int Array[SIZE]);

void CheckShotSeparator(char Field[SIZE][SIZE], int X, int Y) {
  if (X - 1 >= 0 && Y + 1 < SIZE) {
    SetSeparator(Field, X - 1, Y + 1);
  };
  if (X + 1 < SIZE && Y + 1 < SIZE) {
    SetSeparator(Field, X + 1, Y + 1);
  };
  if (X - 1 >= 0 && Y - 1 >= 0) {
    SetSeparator(Field, X - 1, Y - 1);
  };
  if (X + 1 < SIZE && Y - 1 >= 0) {
    SetSeparator(Field, X + 1, Y - 1);
  };
}

void SetKillSeparators(int NumShip, int Side) {
  if (Side == 1) {
    if (NumShip < 6) {
      int x1 = EnemyKillSeparatorsX[NumShip][0];
      int x2 = EnemyKillSeparatorsX[NumShip][1];
      int y1 = EnemyKillSeparatorsY[NumShip][0];
      int y2 = EnemyKillSeparatorsY[NumShip][1];
      if ((x1 >= 0) && (x1 < SIZE) && (y1 >= 0) && (y1 < SIZE)) {
        PlayerShotsField[x1][y1] = '*';
      }
      if ((x2 >= 0) && (x2 < SIZE) && (y2 >= 0) && (y2 < SIZE)) {
        PlayerShotsField[x2][y2] = '*';
      }
    }
    else {
      int x = EnemyKillSmallSeparators[NumShip - 6][0];
      int y = EnemyKillSmallSeparators[NumShip - 6][1];
      if (x - 1 >= 0) {
        PlayerShotsField[x - 1][y] = '*';
      }
      if (x + 1 < SIZE) {
        PlayerShotsField[x + 1][y] = '*';
      }
      if (y - 1 >= 0) {
        PlayerShotsField[x][y - 1] = '*';
      }
      if (y + 1 < SIZE) {
        PlayerShotsField[x][y + 1] = '*';
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
    printf("%d %d\n", X, Y);
    if ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE) && (PlayerShotsField[X][Y] != '#') && (PlayerShotsField[X][Y] != '*')) {
      if (EnemyField[X][Y] != '0') {
        PlayerShotsField[X][Y] = '#';
        CheckShotSeparator(PlayerShotsField, X, Y);
        int NumShip = (int)EnemyField[X][Y] - 65;
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
        OutPutField(PlayerField, EnemyField);
      }
    else {
      printf("Error. Try again.\n");
    }
  }
  return 0;
}

int GenerateShotCoordinate() {
  int Y, X, Status = 1, Array[SIZE], i = SIZE;
  while (Status == 1) {
    i++;
    if(i >= SIZE) {
      RandomArray(Array);
      i = 0;
    }
    X = Array[i];
    Y = Array[i+1];
    if (PlayerField[X][Y] == '*' || PlayerField[X][Y] == '#') {
      continue;
    }
    else {
      Status = 0;
      if (PlayerField[X][Y] != '0') {
        XodBot = 1;
        Memory = 1;
        int NumShip = (int)PlayerField[X][Y] - 65;
        HealthPlayerShip[NumShip] -= 1;
        PlayerHP -= 1;
        if (PlayerHP == 0) return 2;
        PlayerField[X][Y] = '#';
        CheckShotSeparator(PlayerField, X, Y);
        if (HealthPlayerShip[NumShip] == 0) {
          SetKillSeparators(NumShip, 2);
        }
      }
      else {
        PlayerField[X][Y] = '*';
        XodBot = 0;
      }
    }
  }
  OutPutField(PlayerField, EnemyField);
  return 0;
}

int FinishShotCoordinate() {
  printf("Finish Hit!\n" );
  Memory = 0;
}
