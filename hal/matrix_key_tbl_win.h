/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _MATRIX_KEY_TBL_
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _matrix_key_tbl_win_
#define _matrix_key_tbl_win_

//=============================================================================;
// 配置引用区
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//

//-----------------------------------------------------------------------------;
//配置区
//

// WIN 键值表
unsigned char           const   matrixkey_win_tbl[] =
{
//---------------------------------------------- 0x00
// C0
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_CTRL,
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_SHIFT,
    iSTD_CAPITAL,   iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_TAB,       iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ESCAPE,    iKEY_TYPE_STD|iKEY_PRESS,
// C1
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_GUI,
    iSTD_QUROPE2,   iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_A,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x10
    iSTD_Q,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_1,         iKEY_TYPE_STD|iKEY_PRESS,
// C2
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iLEFT_ALT,
    iSTD_Z,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_S,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_W,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_2,         iKEY_TYPE_STD|iKEY_PRESS,
// C3
    iSTD_NULL,      iKEY_TYPE_INVALID,
//---------------------------------------------- 0x20
    iSTD_X,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_D,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_E,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_3,         iKEY_TYPE_STD|iKEY_PRESS,
// C4
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_C,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_F,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_R,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x30
    iSTD_4,         iKEY_TYPE_STD|iKEY_PRESS,
// C5
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_V,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_G,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_T,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_5,         iKEY_TYPE_STD|iKEY_PRESS,
// C6
    iSTD_SPACE,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_B,         iKEY_TYPE_STD|iKEY_PRESS,
//---------------------------------------------- 0x40
    iSTD_H,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_Y,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_6,         iKEY_TYPE_STD|iKEY_PRESS,
// C7
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_N,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_J,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_U,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_7,         iKEY_TYPE_STD|iKEY_PRESS,
// C8
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_M,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_K,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_I,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_8,         iKEY_TYPE_STD|iKEY_PRESS,
// C9
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_ALT,
    iSTD_COMMA,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_L,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_O,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_9,         iKEY_TYPE_STD|iKEY_PRESS,
// C10
    iMODE_KEY_FN,   iKEY_TYPE_SPECIAL,
    iSTD_FULLSTOP,  iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SEMICOLON, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_P,         iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_0,         iKEY_TYPE_STD|iKEY_PRESS,
// C11
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_CTRL,
    iSTD_SLASH,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_QUOTATION_SIGN, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_LEFT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SUBTRACT,  iKEY_TYPE_STD|iKEY_PRESS,
// C12
    iSTD_LEFT,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,      iKEY_TYPE_STD|iKEY_PRESS|iRIGHT_SHIFT,
    iSTD_ENTER,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_SQUARE_BRACKET_RIGHT, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_ADD,       iKEY_TYPE_STD|iKEY_PRESS,
// C13
    iSTD_DOWN,      iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_UP,        iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_NULL,      iKEY_TYPE_INVALID,
    iSTD_BACKSLASH, iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_BACKSPACE, iKEY_TYPE_STD|iKEY_PRESS,
// C14
    iSTD_RIGHT,     iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEDOWN,  iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_PAGEUP,    iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_DELETE,    iKEY_TYPE_STD|iKEY_PRESS,
    iSTD_WAVE,      iKEY_TYPE_STD|iKEY_PRESS,
};
//-----------------------------------------------------------------------------;
#endif
