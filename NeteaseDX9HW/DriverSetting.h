#pragma once

#include "RacingGameAssets.h"
#include "DebugApplication.h"
#include "RacingGameApplication.h"
#include "ShadowAssets.h"
#include "ShadowApplication.h"

//#define Assets RacingGameAssets
//#define Application RacingGameApplication
//#define Application DebugApplication

#define Assets ShadowAssets
#define Application ShadowApplication

#define ENABLE_SHADOW true
#define SHADOW_CASCADE_LAYER_NUM 4


const static int SHADOW_MAP_WIDTH = 2048, SHADOW_MAP_HEIGHT = 2048;
const static float SHADOW_DISTANCE = 100.0f;

//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.067f, 0.2f, 0.467f };//unity的默认参数
//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.1f, 0.23f, 0.6f };//为了能看到三层
const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.2f, 0.467f, 0.75f };//效果好的参数
//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.99f, 0.993f, 0.995f };//模拟没有层级阴影

const static int WIDTH = 1024, HEIGHT = 768;