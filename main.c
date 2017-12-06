#include <stdio.h>

#define SIZE 11


void InputShip() {
  int x, y;
  char direction;
  printf("Input left top coordinate(x, y) and direction ship(x, y, [h, v]): ");
  scanf("%d%d%c", &x, &y, &direction);
}

void OutPutField(char Field[SIZE][SIZE]) {
  for (int i = 0; i <= 10; i++) {
    for (int j = 0; j <= 10; j++) {
      printf("%c ", Field[i][j]);
    }
  printf("\n");
  }
}


int main () {
  char PlayerField[SIZE][SIZE] = {
    {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'},
    {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'3', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'5', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'6', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'8', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
    {'9', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
  };

  int surface[10][10];

    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        surface[i][j] = 0;
      }
    }

   const char alp[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

    printf("   ");
    for (int i = 0; i < 10; i++) {
      printf("%c ", alp[i]);
    }
    printf("\n");
    for (int i = 0; i < 10; i++) {
      printf("%d  ", i);
      for (int j = 0; j < 10; j++) {
        printf("%d ", surface[i][j]);
      }
      printf("\n");
    }



//OutPutField(PlayerField);
//InputShip();

  int n;
  scanf("%d", &n);
}
