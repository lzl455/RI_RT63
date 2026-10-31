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
unsigned char               rgb_index;

//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_mode_breath
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_breath(void)
{
    unsigned char i;

    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

    i = pwm_time_count;
    if(!bback_led_status)
    {
        if(pwm_time_count >= iPWM_MAX)
            pwm_value = 0;
        else
            pwm_value = (iPWM_MAX - i);
    }
    else
    {
        if(pwm_time_count >= iPWM_MAX)
            pwm_value = iPWM_MAX;
        else
            pwm_value = i;
    }

    if(pwm_time_count == iPWM_MAX)   // 最亮和最暗的时间加长
    {
        pwm_time_count = 0;
        bback_led_status = ~bback_led_status;
        if(bback_led_status)
            rgb_index++;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x07];

    for(i=0; i<iLED_NUM_MAX; i++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = ((rgb_index+i)&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        if(br_enable)
            pwm_r_array[i] = pwm_value;
        else
            pwm_r_array[i] = 0;
        if(bg_enable)
            pwm_g_array[i] = pwm_value;
        else
            pwm_g_array[i] = 0;
        if(bb_enable)
            pwm_b_array[i] = pwm_value;
        else
            pwm_b_array[i] = 0;
    }

    pwm_time_count++;
}
