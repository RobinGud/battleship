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

void InputShip() {
  int x, y;
  char direction;
  printf("Input left top coordinate(x, y) and direction ship(x, y, [h, v]): ");
  scanf("%d%d%c", &x, &y, &direction);
}

void OutPutField(char Field[SIZE][SIZE]) {
  const char alp[SIZE] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

  printf("   ");
  for (int i = 0; i < SIZE; i++) {
    printf("%c ", alp[i]);
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

  char PlayerField[SIZE][SIZE];
  FillField(PlayerField);
  OutPutField(PlayerField);

  system ("pause");
  return 0;
}
