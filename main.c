#include "functions.h"

char PlayerField[SIZE][SIZE];
char PlayerShotsField[SIZE][SIZE];
char EnemyField[SIZE][SIZE];
int PlayerKillSmallSeparators[4][2];
int PlayerKillSeparatorsX[6][2];
int PlayerKillSeparatorsY[6][2];
int EnemyKillSmallSeparators[4][2];
int EnemyKillSeparatorsX[6][2];
int EnemyKillSeparatorsY[6][2];

int main () {

  FillField(PlayerField);
  FillField(PlayerShotsField);
  FillField(PlayerShotsField);
  OutPutField(PlayerField, PlayerShotsField);
  poo(PlayerField);
  printf("\n");
  for( int i = 0; i < 6; i++) {
    printf("%d %d   %d %d \n",PlayerKillSeparatorsX[i][0], PlayerKillSeparatorsY[i][0], PlayerKillSeparatorsX[i][1], PlayerKillSeparatorsY[i][1] );
  }
  system ("pause");
  return 0;
}
