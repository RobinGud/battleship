#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//const int SIZE = 10;
#define SIZE 10

int Random(int MaxNum) {
  srand(time(NULL));
  int Num = rand() % MaxNum;
  return Num;
}

int RandomArray(int Array[SIZE]) {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        Array[i] = rand() % SIZE;
    }
}

void FillField(char Field[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      Field[i][j] = '0';
    }
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

int SetHorizontalShip(char Field[SIZE][SIZE], int X, int Y, int LenShip) {
  for(int i = X; i < X + LenShip; i++) {
    Field[Y][i] = '1';
    CheckSeparator(Field, Y, i);
  }
}

int SetVerticalShip(char Field[SIZE][SIZE], int X, int Y,int LenShip) {
  for(int i = Y; i < Y + LenShip; i++) {
    Field[i][X] = '1';
    CheckSeparator(Field, i, X);
  }
}

int CheckHorizontalCoordinate(char Field[SIZE][SIZE], int X, int Y, int LenShip) {
  if (X + LenShip > SIZE) {
      return 1;
  }
    for(int i = X; i < X + LenShip; i++) {
      if (Field[Y][i] != '0')
        return 1;
  }
  SetHorizontalShip(Field, X, Y, LenShip);
  return 0;
}

int CheckVerticalCoordinate(char Field[SIZE][SIZE], int X, int Y, int LenShip) {
  if (Y + LenShip > SIZE) {
    return 1;
  }
  for(int i = Y; i < Y + LenShip; i++) {
      if (Field[i][X] != '0')
        return 1;
  }
  SetVerticalShip(Field, X, Y, LenShip);
  return 0;
}

void InputShip(int LenShip, char Field[SIZE][SIZE]) {
  int Y, Status = 1, X;
  char charX, Direction;
  while (Status == 1) {
    printf("Input left top coordinate and direction for %d deck ship(x, y, [h, v]): ", LenShip);
    scanf("%1c%1d%1c", &charX, &Y, &Direction);
    fflush(stdin);
    X = (int)charX - 97;
    if ((X >= 0) && (X <= 9) && (Y >= 0) && (Y <= 9) && ((Direction == 'h') || (Direction == 'v')))
      (Direction == 'h') ? (Status = CheckHorizontalCoordinate(Field, X, Y, LenShip)) : (Status = CheckVerticalCoordinate(Field, X, Y, LenShip));
    if (Status == 1)
      printf("Error. Try again.\n");
  }
}

void GenerateShip(int LenShip, char Field[SIZE][SIZE]){
  int Y, X, Direction, Status = 1, i = SIZE, Array[SIZE];
  while(Status == 1) {
    i++;
    if (i >= SIZE) {
      RandomArray(Array);
      i = 0;
    }
    X = Array[i];
    Y = Array[i+1];
    Direction = Random(2);
    (Direction == 1) ?  (Status = CheckHorizontalCoordinate(Field, X, Y, LenShip)) : (Status = CheckVerticalCoordinate(Field, X, Y, LenShip));
  }
}

void OutPutField(char Field[SIZE][SIZE]) {
  const char Alp[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  printf("   ");
  for (int i = 0; i < SIZE; i++) {
    printf("%c ", Alp[i]);
  }
  printf("\n");
  for (int i = 0; i < SIZE; i++) {
    printf("%d  ", i);
    for (int j = 0; j < SIZE; j++) {
      printf("%c ", Field[i][j]);
    }
    printf("\n");
  }
}

int main () {
  int LenShips[SIZE] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
  char PlayerField[SIZE][SIZE];
  char EnemyField[SIZE][SIZE];
  //FillField(PlayerField);
  //OutPutField(PlayerField);
  //for (int i = 0; i < SIZE; i++) {
    //InputShip(LenShips[i], PlayerField);
    //OutPutField(PlayerField);
  //}
  FillField(EnemyField);
  for (int i = 0; i < SIZE; i++) {
    GenerateShip(LenShips[i], EnemyField);
  }
  OutPutField(EnemyField);

  system ("pause");
  return 0;
}
