#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

void FillField(char Field[SIZE][SIZE]) {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      Field[i][j] = '0';
    }
  }
}

void InputShip(int LenShip) {
  int y;
  char x, direction;
  printf("Input left top coordinate and direction for %d deck ship(x, y, [h, v]): ", LenShip);
  scanf("%c%d%c", &x, &y, &direction);
  fflush(stdin);

}
/*
void SetHorizontalShip(char Field[SIZE][SIZE]) {

}

void SetVerticalShip(char Field[SIZE][SIZE]) {

}
*/
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
  InputShip(LenShips[i]);
  }

  system ("pause");
  return 0;
}
