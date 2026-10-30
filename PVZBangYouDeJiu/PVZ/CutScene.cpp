#include "Board.h"
#include "Cutscene.h"
#include "LawnApp.h"
#include "Resources.h"
#include "LawnDialog.h"
#include "GameButton.h"

using namespace Sexy;

bool CutScene::IsSurvivalRepick()
{
    uintptr_t func = 0x43A710;
    bool result;

    _asm
    {
        mov edx, this;
        call func;
        mov result, al;
    }
    return result;
}
