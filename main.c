#include <stdio.h>
#include <stdlib.h>

const int SIZE = 10;

void FillField(char Field[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      Field[i][j] = '0';
    }
  }
}

int SetHorizontalShip(char Field[SIZE][SIZE], int X, int Y, int LenShip) {
  for(int i = X; i < X + LenShip; i++)
    Field[Y][i] = '1';
}

int SetVerticalShip(char Field[SIZE][SIZE], int X, int Y,int LenShip) {
  for(int i = Y; i < Y + LenShip; i++)
    Field[i][X] = '1';
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

void InputShip(int LenShip, char Field[SIZE][SIZE] ) {
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
  FillField(PlayerField);
  OutPutField(PlayerField);

  for (int i = 0; i < SIZE; i++) {
    InputShip(LenShips[i], PlayerField);
    OutPutField(PlayerField);
  }

  system ("pause");
  return 0;
}
