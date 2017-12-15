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

int LenShips[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
char Alp[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

void FillField(char Field[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      Field[i][j] = '0';
    }
  }
}

void OutPutField(char FirstField[SIZE][SIZE], char SecondField[SIZE][SIZE]) {
  system("clear");
  printf("       Your Field                         Enemy Field\n" );
  printf("   ");
  for (int i = 0; i < SIZE; i++) {
    printf("%c ", Alp[i]);
  }
  printf("               ");
  for (int i = 0; i < SIZE; i++) {
    printf("%c ", Alp[i]);
  }
  printf("\n");

  for(int i = 0; i < SIZE; i++) {
    printf("%d  ", i);
    for(int j = 0; j < SIZE; j++) {
      printf("%c ", FirstField[i][j]);
    }
    printf("            %d  ", i);
    for(int j = 0; j < SIZE; j++) {
      printf("%c ", SecondField[i][j]);
    }
    printf("\n");
  }

}

void SetSeparator(char Field[SIZE][SIZE], int X, int Y) {
  if (Field[X][Y] == '0') {
    Field[X][Y] = '*';
  }
}

void CheckSeparator(char Field[SIZE][SIZE], int X, int Y) {
  if (X - 1 >= 0 && Y + 1 < SIZE) {
    SetSeparator(Field, X - 1, Y + 1);
  };
  if (Y + 1 < SIZE) {
    SetSeparator(Field, X, Y + 1);
  };
  if (X + 1 < SIZE && Y + 1 < SIZE) {
    SetSeparator(Field, X + 1, Y + 1);
  };
  if (X - 1 >= 0) {
    SetSeparator(Field, X - 1, Y);
  };
  if (X + 1 < SIZE) {
    SetSeparator(Field, X + 1, Y);
  };
  if (X - 1 >= 0 && Y - 1 >= 0) {
    SetSeparator(Field, X - 1, Y - 1);
  };
  if (Y - 1 >= 0) {
    SetSeparator(Field, X, Y - 1);
  };
  if (X + 1 < SIZE && Y - 1 >= 0) {
    SetSeparator(Field, X + 1, Y - 1);
  };
}

int SetHorizontalShip(char Field[SIZE][SIZE], int X, int Y, int NumShip) {
  if (Y + LenShips[NumShip] > SIZE) {
    return 1;
  }
  for(int i = Y; i < Y + LenShips[NumShip]; i++) {
    if (Field[X][i] != '0')
      return 1;
}
  for(int i = Y; i < Y + LenShips[NumShip]; i++) {
    Field[X][i] = Alp[NumShip];;
    CheckSeparator(Field, X, i);
  }

  PlayerKillSeparatorsX[NumShip][0] = X ;
  PlayerKillSeparatorsY[NumShip][0] = Y - 1;
  PlayerKillSeparatorsX[NumShip][1] = X;
  PlayerKillSeparatorsY[NumShip][1] = Y + LenShips[NumShip] + 1;
  return 0;
}

int SetVerticalShip(char Field[SIZE][SIZE], int X, int Y, int NumShip) {
  if (X + LenShips[NumShip] > SIZE) {
    return 1;
  }
  for(int i = X; i < X + LenShips[NumShip]; i++) {
    if (Field[i][Y] != '0')
      return 1;
}
  for(int i = X; i < X + LenShips[NumShip]; i++) {
    Field[i][Y] = Alp[NumShip];;
    CheckSeparator(Field, i, Y);
  }
  PlayerKillSeparatorsX[NumShip][0] = X - 1;
  PlayerKillSeparatorsY[NumShip][0] = Y;
  PlayerKillSeparatorsX[NumShip][1] = X + LenShips[NumShip] + 1;
  PlayerKillSeparatorsY[NumShip][1] = Y;
  return 0;
}

void SetBigShip(char Field[SIZE][SIZE], int NumShip) {
    int Y, Status = 1, X;
    char charY, Direction;
    while (Status == 1) {
      printf("Input left top coo  rdinate and direction for %d deck ship(x, y, [h, v]): ", LenShips[NumShip]);
      scanf("%1c%1d%1c", &charY, &X, &Direction);
      fflush(stdin);
      Y = (int)charY - 97;
      if ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE) && (Direction == 'h'))
        Status = SetHorizontalShip(Field, X, Y, NumShip);
      if ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE) && (Direction == 'v'))
        Status = SetVerticalShip(Field, X, Y, NumShip);
      if (Status == 1)
        printf("Error. Try again.\n");
    }
}

void SetSmallShip(char Field[SIZE][SIZE],int NumShip) {
  int Y, Status = 1, X;
  char charY;
  while (Status == 1) {
    printf("Input left top coordinate for 1 deck ship(x, y): ");
    scanf("%1c%1d", &charY, &X);
    fflush(stdin);
    Y = (int)charY - 97;
    if ((X >= 0) && (X < SIZE) && (Y >= 0) && (Y < SIZE) && (PlayerField[X][Y] == '0')) {
      PlayerField[X][Y] = Alp[NumShip];
      PlayerKillSmallSeparators[NumShip - 6][0] = X;
      PlayerKillSmallSeparators[NumShip - 6][1] = Y;
      CheckSeparator(Field, X, Y);
      Status = 0;
    }
    if (Status == 1)
      printf("Error. Try again.\n");
  }
}

void poo(char Field[SIZE][SIZE]) {
  for(int i = 0; i < SIZE; i++) {
    if (LenShips[i] == 1) {
      SetSmallShip(Field, i);
    }
    else {
      SetBigShip(Field, i);
    }
    OutPutField(PlayerField, PlayerShotsField);
  }
}
