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

#define iROLLING_INDEX_MAX      90
#define iROLLING_PWM_SWITCH     150

unsigned char                   nhjb_led_index;

//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_nhjb(void)
{
    unsigned char i;

    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

    if(0 == nhjb_led_index)
    {
        pwm_duty_array_0[1]++;
        if(iPWM_MAX <= pwm_duty_array_0[1])
            nhjb_led_index++;
    }
    else if(1 == nhjb_led_index)
    {
        pwm_duty_array_0[0]--;
        if(0 == pwm_duty_array_0[0])
            nhjb_led_index++;
    }
    else if(2 == nhjb_led_index)
    {
        pwm_duty_array_0[2]++;
        if(iPWM_MAX <= pwm_duty_array_0[2])
            nhjb_led_index++;
    }
    else if(3 == nhjb_led_index)
    {
        pwm_duty_array_0[1]--;
        if(0 == pwm_duty_array_0[1])
            nhjb_led_index++;
    }
    else if(4 == nhjb_led_index)
    {
        pwm_duty_array_0[0]++;
        if(iPWM_MAX <= pwm_duty_array_0[0])
            nhjb_led_index++;
    }
    else //if(5 == nhjb_led_index)
    {
        pwm_duty_array_0[2]--;
        if(0 == pwm_duty_array_0[2])
            nhjb_led_index = 0;
    }

    for(i=0; i<iMATRIX_NUM_MAX; i++)
    {
        pwm_r_array[i] = pwm_duty_array_0[0];
        pwm_g_array[i] = pwm_duty_array_0[1];
        pwm_b_array[i] = pwm_duty_array_0[2];
    }
}


