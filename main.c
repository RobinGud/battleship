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
enum MEM Memory = MEM_VOID;
int DirMem = 0;
int XMem = 0;
int YMem = 0;
int WinFlag = 0;
int XodBot = 0;

int main () {
  LocationShip();
  while(WinFlag == false) {
    if (XodBot == 0) {
      WinFlag = InputShotCoordinate();
    }
    if (WinFlag == true) break;
    if (Memory == MEM_VOID) {
      WinFlag = GenerateShotCoordinate();
    }
    else if (Memory == MEM_POINT) {
      WinFlag = DirFindShotCoordintare();
    }
    else {
      WinFlag = FindFinishShotCoordinate();
    }
    OutPutField(PlayerField, PlayerShotsField);
  }

  OutPutField(PlayerField, PlayerShotsField);
  if (WinFlag == true) {
    printf("Good job! You Win!\n" );
  }
  else {
    printf("Don't worry! You lost :(\n" );
  }
  system ("pause");
  return 0;
}
