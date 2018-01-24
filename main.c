#include "main.h"
#include "functionsLocated.c"
#include "functionsShots.c"

int main () {
  LocationShip();
  while(!WinFlag) {
    if (!XodBot) {
      WinFlag = InputShotCoordinate();
    }
    if (WinFlag) break;
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
  if (WinFlag) {
    printf("Good job! You Win!\n" );
  }
  else {
    printf("Don't worry! You lost :(\n" );
  }
  system ("pause");
  return 0;
}
