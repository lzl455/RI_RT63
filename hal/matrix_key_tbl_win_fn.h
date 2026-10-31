/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _MATRIX_KEY_TBL_
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _matrix_key_tbl_win_fn_
#define _matrix_key_tbl_win_fn_

//=============================================================================;
// 配置引用区
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//

//-----------------------------------------------------------------------------;
//配置区
//

// WIN FN键值表
unsigned char           const   matrixkey_win_fn_tbl[] =
{
//---------------------------------------------- 0x00
// C0
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,
    iSTD_CAPITAL,   iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_TAB,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,      iKEY_TYPE_INVALID,
// C1
    iKEY_WIN_LOCK,  iKEY_TYPE_SPECIAL,
    iSTD_QUROPE2,   iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_A,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x10
    iMODE_KEY_24G,  iKEY_TYPE_SPECIAL,
    iSTD_F1,        iKEY_TYPE_STD|iKEY_PRESS, 
// C2
    iLED_TEST,      iKEY_TYPE_SPECIAL,
    iSTD_Z,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_S,         iKEY_TYPE_STD|iKEY_PRESS,
    iMODE_KEY_BT0,  iKEY_TYPE_SPECIAL,
    iSTD_F2,        iKEY_TYPE_STD|iKEY_PRESS,
// C3
    iSTD_NULL,      iKEY_TYPE_INVALID,
//---------------------------------------------- 0x20
    iSTD_X,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_D,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_E,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F3,        iKEY_TYPE_STD|iKEY_PRESS,
// C4
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_C,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_R,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x30
    iSTD_F4,        iKEY_TYPE_STD|iKEY_PRESS, 
// C5
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_V,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_G,         iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MEDIA_SELECT_L, iKEY_TYPE_MMK|iMMK_MEDIA_SELECT_H,
    iSTD_F5,        iKEY_TYPE_STD|iKEY_PRESS,
// C6
    iSTD_SPACE,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_B,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x40
    iSTD_H,         iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_VOLUMEDOWN_L, iKEY_TYPE_MMK|iMMK_VOLUMEDOWN_H,
    iSTD_F6,        iKEY_TYPE_STD|iKEY_PRESS,
// C7
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_N,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_J,         iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_VOLUMEUP_L, iKEY_TYPE_MMK|iMMK_VOLUMEUP_H,
    iSTD_F7,        iKEY_TYPE_STD|iKEY_PRESS,
// C8
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_M,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_K,         iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_MUTE_L,    iKEY_TYPE_MMK|iMMK_MUTE_H,
    iSTD_F8,        iKEY_TYPE_STD|iKEY_PRESS,
// C9
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,
    iSTD_SNAPSHOT,  iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_L,         iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_STOP_L,    iKEY_TYPE_MMK|iMMK_STOP_H,
    iSTD_F9,        iKEY_TYPE_STD|iKEY_PRESS,
// C10
    iMODE_KEY_FN,   iKEY_TYPE_SPECIAL,
    iSTD_SCROLL,    iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_HOME,      iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_PREV_TRACK_L, iKEY_TYPE_MMK|iMMK_PREV_TRACK_H,
    iSTD_F10,       iKEY_TYPE_STD|iKEY_PRESS,
// C11
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL,
    iSTD_PAUSE,     iKEY_TYPE_STD|iKEY_PRESS, 
    iSTD_END,       iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_PLAY_PAUSE_L, iKEY_TYPE_MMK|iMMK_PLAY_PAUSE_H,
    iSTD_F11,       iKEY_TYPE_STD|iKEY_PRESS,
// C12
    iLED_MODE_CYC_ADD, iKEY_TYPE_SPECIAL,
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,
    iSTD_ENTER,     iKEY_TYPE_STD|iKEY_PRESS,
    iMMK_NEXT_TRACK_L, iKEY_TYPE_MMK|iMMK_NEXT_TRACK_H,
    iSTD_F12,       iKEY_TYPE_STD|iKEY_PRESS,
// C13
    iLED_BRIGHT_SUB, iKEY_TYPE_SPECIAL,
    iLED_BRIGHT_ADD, iKEY_TYPE_SPECIAL,
    iSTD_NULL,       iKEY_TYPE_INVALID,
    iKEY_CLR_BTE_INFO, iKEY_TYPE_SPECIAL,
    iKEY_FX_LOCK,    iKEY_TYPE_SPECIAL,
// C14
    iLED_SPEED_CYC_ADD, iKEY_TYPE_SPECIAL,
    iSTD_END,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_HOME,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_INSERT,    iKEY_TYPE_STD|iKEY_PRESS,//iLED_RGB_SWTICH, iKEY_TYPE_SPECIAL,
    iSTD_SNAPSHOT,  iKEY_TYPE_STD|iKEY_PRESS
};
//-----------------------------------------------------------------------------;
#endif
