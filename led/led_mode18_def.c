 /*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: uart.c
*
* 功能说明: 
* 修改说明:
*******************************************************************************/
#include "..\defines.h"

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_mode_bhqf
* 功能描述: 百花齐放
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_def(void)
{
    unsigned char i;
    unsigned char dat_l, dat_h;

    if(0 == scan_index)
    {
        scan_index= 1;
        gtemp_i = (iLED_MAX_BHQF)*0/4;
    }
    else if(1 == scan_index)
    {
        scan_index= 2;
        gtemp_i = (iLED_MAX_BHQF)*1/4;
    }
    else if(2 == scan_index)
    {
        scan_index= 3;
        gtemp_i = (iLED_MAX_BHQF)*2/4;
    }
    else //if(3 == scan_index)
    {
        scan_index= 0;
        gtemp_i = (iLED_MAX_BHQF)*3/4;
    }

    gtemp_j = (gtemp_i<<1);
    for(i=0; i<(iLED_MAX_BHQF/4); i++)
    {
        dat_l = led_def_tbl[gtemp_j++];
        dat_h = led_def_tbl[gtemp_j++];

        pwm_r_array[gtemp_i] = ((dat_l<<2)&0x7C);
        pwm_g_array[gtemp_i] = ((dat_l>>5)|(dat_h<<5)&0x7C);
        pwm_b_array[gtemp_i] = (dat_h&0x7C);

        gtemp_i++;
    }
}
