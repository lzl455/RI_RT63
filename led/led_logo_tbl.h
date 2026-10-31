/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: _LED_TBL_
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_LOGO_TBL_
#define _LED_LOGO_TBL_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

#define iR                      5

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define NULL_0                  127
#define NULL_1                  126
#define NULL_2                  125
#define NULL_3                  124
#define NULL_4                  123
#define NULL_5                  122
#define NULL_6                  121
#define NULL_7                  120

//-----------------------------------------------------------------------------;
//配置区
//
#define RGB_COLOR_MAX         8
#define RGB_COLOR_INIT        7

unsigned char       const   rgb_en_tbl[]={
    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,
    iPWM_R|iPWM_G|iPWM_B,

    iPWM_R,
    iPWM_G,
    iPWM_B,
    iPWM_R|iPWM_B,
    iPWM_R|iPWM_G,
    iPWM_G|iPWM_B,
    iPWM_W,
    iPWM_R|iPWM_G|iPWM_B,

    0x0F,
};

unsigned char       const       led_snake_table[iLED_NUM_MAX] =
{
//HOME    NULL    back    +       -       0       9       8       7       6        5      4       3       2
  iR*14+4,iR*13+4,iR*12+4,iR*11+4,iR*10+4,iR*9+4, iR*8+4, iR*7+4, iR*6+4, iR*5+4, iR*4+4, iR*3+4, iR*2+4, iR*1+4, iR*0+4,
//TBL     Q       W       E       R       T       Y       U       I       O       P       [       ]       NULL    
  iR*0+3, iR*1+3, iR*2+3, iR*3+3, iR*4+3, iR*5+3, iR*6+3, iR*7+3, iR*8+3, iR*9+3, iR*10+3,iR*11+3,iR*12+3,iR*13+3,iR*14+3,
//PD      NULL    Inter   NULL    '       ;       L       K       J       H       G       F       D       S
  iR*14+2,iR*13+2,iR*12+2,iR*11+2,iR*10+2,iR*9+2, iR*8+2, iR*7+2, iR*6+2, iR*5+2, iR*4+2, iR*3+2, iR*2+2, iR*1+2, iR*0+2,
//SHIFT   NULL    Z       X       C       V       B       N       M       ,       .       /       SHIFT   NULL
  iR*0+1, iR*1+1, iR*2+1, iR*3+1, iR*4+1, iR*5+1, iR*6+1, iR*7+1, iR*8+1, iR*9+1, iR*10+1,iR*11+1,iR*12+1,iR*13+1,iR*14+1,
//RIGHT   DOWN    LEFT    CTRL    FN      ALT     NULL    NULL    NULL    SPACE   NULL    NULL    NULL    ALT
  iR*14+0,iR*13+0,iR*12+0,iR*11+0,iR*10+0,iR*9+0, iR*8+0, iR*7+0, iR*6+0, iR*5+0, iR*4+0, iR*3+0, iR*2+0, iR*1+0, iR*0+0,
};

unsigned char       const       led_to_matrix_tab_3[]=
{
//CTRL    WIN     ALT     NULL    NULL    NULL    SPACE   NULL    NULL    NULL    ALT     FN      CTRL    LEFT    LEFT    
  iR*0+0, iR*1+0, iR*2+0, iR*3+0, iR*4+0, iR*5+0, iR*6+0, iR*7+0, iR*8+0, iR*9+0, iR*10+0,iR*11+0,iR*12+0,iR*13+0,iR*14+0,
//SHIFT   NULL    Z       X       C       V       B       N       M       ,       .       /       SHIFT   NULL    NULL    
  iR*0+1, iR*1+1, iR*2+1, iR*3+1, iR*4+1, iR*5+1, iR*6+1, iR*7+1, iR*8+1, iR*9+1, iR*10+1,iR*11+1,iR*12+1,iR*13+1,iR*14+1,
//Caps    A       S       D       F       G       H       J       K       L       ;       '       NULL    Inter   Inter   
  iR*0+2, iR*1+2, iR*2+2, iR*3+2, iR*4+2, iR*5+2, iR*6+2, iR*7+2, iR*8+2, iR*9+2, iR*10+2,iR*11+2,iR*12+2,iR*13+2,iR*14+2,
//TBL     Q       W       E       R       T       Y       U       I       O       P       [       ]       NULL    NULL    
  iR*0+3, iR*1+3, iR*2+3, iR*3+3, iR*4+3, iR*5+3, iR*6+3, iR*7+3, iR*8+3, iR*9+3, iR*10+3,iR*11+3,iR*12+3,iR*13+3,iR*14+3,
//~       1       2       3       4       5       6       7       8       9       0       -       +       back    back    
  iR*0+4, iR*1+4, iR*2+4, iR*3+4, iR*4+4, iR*5+4, iR*6+4, iR*7+4, iR*8+4, iR*9+4, iR*10+4,iR*11+4,iR*12+4,iR*13+4,iR*14+4,
};

unsigned char       const       led_to_matrix_tab_4[]=
{
//LEFT    LEFT    CTRL    FN      ALT     NULL    NULL    NULL    SPACE   NULL    NULL    NULL    ALT     WIN     CTRL   
  iR*14+0,iR*13+0,iR*12+0,iR*11+0,iR*10+0,iR*9+0, iR*8+0, iR*7+0, iR*6+0, iR*5+0, iR*4+0, iR*3+0, iR*2+0, iR*1+0, iR*0+0,
//NULL    NULL    SHIFT   /       .       ,       M       N       B       V       C       X       Z       NULL    SHIFT  
  iR*14+1,iR*13+1,iR*12+1,iR*11+1,iR*10+1,iR*9+1, iR*8+1, iR*7+1, iR*6+1, iR*5+1, iR*4+1, iR*3+1, iR*2+1, iR*1+1, iR*0+1,
//Inter   Inter   NULL    '       ;       L       K       J       H       G       F       D       S       A       Caps   
  iR*14+2,iR*13+2,iR*12+2,iR*11+2,iR*10+2,iR*9+2, iR*8+2, iR*7+2, iR*6+2, iR*5+2, iR*4+2, iR*3+2, iR*2+2, iR*1+2, iR*0+2,
//NULL    NULL    ]       [       P       O       I       U       Y       T       R       E       W       Q       TBL    
  iR*14+3,iR*13+3,iR*12+3,iR*11+3,iR*10+3,iR*9+3, iR*8+3, iR*7+3, iR*6+3, iR*5+3, iR*4+3, iR*3+3, iR*2+3, iR*1+3, iR*0+3,
//back    back    +       -       0       9       8       7       6       5       4       3       2       1       ~      
  iR*14+4,iR*13+4,iR*12+4,iR*11+4,iR*10+4,iR*9+4, iR*8+4, iR*7+4, iR*6+4, iR*5+4, iR*4+4, iR*3+4, iR*2+4, iR*1+4, iR*0+4,
};
/*
unsigned char       const       led_to_matrix_tab_1[]=
{
//CTRL   SHIFT  Caps   tbl    ~      ESC
  iR*0+0, iR*0+1, iR*0+2, iR*0+3, iR*0+4, iR*0+5,
//WIN    NULL   A      Q      1      F1
  iR*1+0, iR*1+1, iR*1+2, iR*1+3, iR*1+4, iR*1+5,
//ALT    Z      S      W      2      F2
  iR*2+0, iR*2+1, iR*2+2, iR*2+3, iR*2+4, iR*2+5,
//NULL   X      D      E      3      F3
  iR*3+0, iR*3+1, iR*3+2, iR*3+3, iR*3+4, iR*3+5,
//NULL   C      F      R      4      F4
  iR*4+0, iR*4+1, iR*4+2, iR*4+3, iR*4+4, iR*4+5,
//NULL   V      G      T      5      F5
  iR*5+0, iR*5+1, iR*5+2, iR*5+3, iR*5+4, iR*5+5,
//SPACE  B      H      Y      6      F6
  iR*6+0, iR*6+1, iR*6+2, iR*6+3, iR*6+4, iR*6+5,
//NULL   N      J      U      7      F7
  iR*7+0, iR*7+1, iR*7+2, iR*7+3, iR*7+4, iR*7+5,
//NULL   M      K      I      8      F8
  iR*8+0, iR*8+1, iR*8+2, iR*8+3, iR*8+4, iR*8+5,
//NULL   ,      L      O      9      F9
  iR*9+0, iR*9+1, iR*9+2, iR*9+3, iR*9+4, iR*9+5,
//ALT    .      ;      P      0      F10
  iR*10+0,iR*10+1,iR*10+2,iR*10+3,iR*10+4,iR*10+5,
//FN     /      '      [      -      F11
  iR*11+0, iR*11+1,iR*11+2,iR*11+3,iR*11+4,iR*11+5,
//CTRL   NULL   NULL   ]      +      F12
  iR*12+0,iR*12+1,iR*12+2,iR*12+3,iR*12+4,iR*12+5,
//LEFT   SHIFT  Inter  \      BACK   PRTSC
  iR*13+0,iR*13+1,iR*13+2,iR*13+3,iR*13+4,iR*13+5,
//DOWN   UP   NULL   1      NULL   PAUSE
  iR*14+0,iR*14+1,iR*14+2,iR*14+3,iR*14+4,iR*14+5,
};*/

unsigned char       const       led_to_matrix_tab_2[iLED_COL_NUM][iLED_ROW_NUM]=
{
//CTRL   SHIFT  Caps   tbl    ~      ESC
  iR*0+0, iR*0+1, iR*0+2, iR*0+3, iR*0+4,
//WIN    NULL   A      Q      1      F1
  iR*1+0, iR*1+1, iR*1+2, iR*1+3, iR*1+4,
//ALT    Z      S      W      2      F2
  iR*2+0, iR*2+1, iR*2+2, iR*2+3, iR*2+4,
//NULL   X      D      E      3      F3
  iR*3+0, iR*3+1, iR*3+2, iR*3+3, iR*3+4,
//NULL   C      F      R      4      F4
  iR*4+0, iR*4+1, iR*4+2, iR*4+3, iR*4+4,
//NULL   V      G      T      5      F5
  iR*5+0, iR*5+1, iR*5+2, iR*5+3, iR*5+4,
//SPACE  B      H      Y      6      F6
  iR*6+0, iR*6+1, iR*6+2, iR*6+3, iR*6+4,
//NULL   N      J      U      7      F7
  iR*7+0, iR*7+1, iR*7+2, iR*7+3, iR*7+4,
//NULL   M      K      I      8      F8
  iR*8+0, iR*8+1, iR*8+2, iR*8+3, iR*8+4,
//NULL   ,      L      O      9      F9
  iR*9+0, iR*9+1, iR*9+2, iR*9+3, iR*9+4,
//ALT    .      ;      P      0      F10
  iR*10+0,iR*10+1,iR*10+2,iR*10+3,iR*10+4,
//FN     /      '      [      -      F11
  iR*11+0,iR*11+1,iR*11+2,iR*11+3,iR*11+4,
//CTRL   NULL   NULL   ]      +      F12
  iR*12+0,iR*12+1,iR*12+2,iR*12+3,iR*12+4,
//LEFT   SHIFT  Inter  \      BACK   PRTSC
  iR*13+0,iR*13+1,iR*13+2,iR*13+3,iR*13+4,
//LEFT   SHIFT  Inter  \      BACK   PRTSC
  iR*14+0,iR*14+1,iR*14+2,iR*14+3,iR*14+4,
};
/*
unsigned char       const   matrix_to_led_tab[] =
{
//CTRL   SHIFT  Caps   tbl    ~      ESC
  iR*0+0, iR*0+1, iR*0+2, iR*0+3, iR*0+4, iR*0+5,
//WIN    NULL   A      Q      1      F1
  iR*1+0, iR*1+1, iR*1+2, iR*1+3, iR*1+4, iR*1+5,
//ALT    Z      S      W      2      F2
  iR*2+0, iR*2+1, iR*2+2, iR*2+3, iR*2+4, iR*2+5,
//NULL   X      D      E      3      F3
  iR*3+0, iR*3+1, iR*3+2, iR*3+3, iR*3+4, iR*3+5,
//NULL   C      F      R      4      F4
  iR*4+0, iR*4+1, iR*4+2, iR*4+3, iR*4+4, iR*4+5,
//NULL   V      G      T      5      F5
  iR*5+0, iR*5+1, iR*5+2, iR*5+3, iR*5+4, iR*5+5,
//SPACE  B      H      Y      6      F6
  iR*6+0, iR*6+1, iR*6+2, iR*6+3, iR*6+4, iR*6+5,
//NULL   N      J      U      7      F7
  iR*7+0, iR*7+1, iR*7+2, iR*7+3, iR*7+4, iR*7+5,
//NULL   M      K      I      8      F8
  iR*8+0, iR*8+1, iR*8+2, iR*8+3, iR*8+4, iR*8+5,
//NULL   ,      L      O      9      F9
  iR*9+0, iR*9+1, iR*9+2, iR*9+3, iR*9+4, iR*9+5,
//ALT    .      ;      P      0      F10
  iR*10+0,iR*10+1,iR*10+2,iR*10+3,iR*10+4,iR*10+5,
//FN     /      '      [      -      F11
  iR*11+0, iR*11+1,iR*11+2,iR*11+3,iR*11+4,iR*11+5,
//CTRL   NULL   NULL   ]      +      F12
  iR*12+0,iR*12+1,iR*12+2,iR*12+3,iR*12+4,iR*12+5,
//LEFT   SHIFT  Inter  \      BACK   PRTSC
  iR*13+0,iR*13+1,iR*13+2,iR*13+3,iR*13+4,iR*13+5,
//DOWN   UP   NULL   1      NULL   PAUSE
  iR*14+0,iR*15+1,iR*14+2,iR*14+3,iR*14+4,iR*14+5,
//RIGHT  END    PD     PU     HOME   DEL
  iR*15+0,iR*15+1,iR*15+2,iR*15+3,iR*15+4,iR*15+5,
};
*/
unsigned char       const   sbzl_r_tbl[]={
 128, 96, 64, 32,  0,  0,  0,  0,  0, 32, 64, 96,128, 96, 64, 32,  0,  0,  0,  0,  0,};
unsigned char       const   sbzl_g_tbl[]={
   0, 32, 64, 96,128, 96, 64, 32,  0,  0,  0,  0,  0, 32, 64, 96,128, 96, 64, 32,  0,};
unsigned char       const   sbzl_b_tbl[]={
   0,  0,  0,  0,  0, 32, 64, 96,128, 96, 64, 32,  0,  0,  0,  0,  0, 32, 64, 96,128,};
unsigned char       const   sbzl_ctrl_tbl[]={
   0,  0,  0,  0,  1,  1,  1,  1,  2,  2,  2,  2,  0,  0,  0,  0,  1,  1,  1,  1,  2,};

//-----------------------------------------------------------------------------;

#endif



