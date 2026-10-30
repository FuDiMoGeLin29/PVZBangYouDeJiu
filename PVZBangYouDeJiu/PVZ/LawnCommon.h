#pragma once
#include "CheckboxListener.h"
#include "Checkbox.h"
#define MAX_GRID_SIZE_X			9
#define LAWN_GRIDXWIDTH			80
#define MAX_GRID_SIZE_Y			6
#define FWOOSH_MAX				100
#define MAX_FLAME_SPREAD_TIME	50
#define MAX_FLAME_LAST_TIME		100

constexpr const int			ADVENTURE_AREAS = 5;
constexpr const int			LEVELS_PER_AREA = 10;
constexpr const int         NUM_LEVELS = ADVENTURE_AREAS * LEVELS_PER_AREA;
constexpr const int			FINAL_LEVEL = NUM_LEVELS;

// 取关卡序号(大关, 小关)
// e.g. 第 17 关（即 2-7 关卡）-> LEVEL(2, 7)
#define LEVEL(area, sub) (((area) - 1) * LEVELS_PER_AREA + (sub))

Sexy::Checkbox* MakeNewCheckbox(int theId, Sexy::CheckboxListener* theListener, bool theDefault);