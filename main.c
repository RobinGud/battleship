#include "functionsLocated.h"
#include "functionsShots.h"

char PlayerField[SIZE][SIZE];
char PlayerShotsField[SIZE][SIZE];
char EnemyField[SIZE][SIZE];
int PlayerKillSmallSeparators[4][2];
int PlayerKillSeparatorsX[6][2];
int PlayerKillSeparatorsY[6][2];
int EnemyKillSmallSeparators[4][2];
int EnemyKillSeparatorsX[6][2];
int EnemyKillSeparatorsY[6][2];
int PlayerHP = 20;
int EnemyHP = 20;

int main () {
  LocationShip();
  InputShotCoordinate();
  OutPutField(PlayerShotsField, EnemyField);

  system ("pause");
  return 0;
}
