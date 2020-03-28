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

//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.067f, 0.2f, 0.467f };//unity��Ĭ�ϲ���
//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.1f, 0.23f, 0.6f };//Ϊ���ܿ�������
const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.2f, 0.467f, 0.75f };//Ч���õĲ���
//const static float CACSCADE_SHADOW_MAP_BOUND_PERCENT[SHADOW_CASCADE_LAYER_NUM - 1] = { 0.99f, 0.993f, 0.995f };//ģ��û�в㼶��Ӱ

const static int WIDTH = 1024, HEIGHT = 768;