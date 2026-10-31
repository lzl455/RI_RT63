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
void led_mode_centre(void)
{
    unsigned char i, x, k;

    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

	k = snake_led_index;
	x = --pwm_duty_array_0[k];

	if(((iPWM_MAX*5)/6)>=x)
    {
		snake_led_index++;
        pwm_duty_array_0[k] = ((iPWM_MAX*5)/6);
        pwm_duty_array_0[snake_led_index] = iPWM_MAX;
    }
	x = pwm_duty_array_0[k];
	k--;
	pwm_duty_array_0[k] = x-((iPWM_MAX*1)/6);
	k--;
	pwm_duty_array_0[k] = x-((iPWM_MAX*2)/6);
	k--;
	pwm_duty_array_0[k] = x-((iPWM_MAX*3)/6);
	k--;
	pwm_duty_array_0[k] = x-((iPWM_MAX*4)/6);
	k--;
	pwm_duty_array_0[k] = x-((iPWM_MAX*5)/6);

	if((iLED_COL_NUM+2) <= snake_led_index)
	{
	    snake_led_index = 5;
        memset(pwm_duty_array_0, 0x00, 34);
	    pwm_duty_array_0[5] = iPWM_MAX;
	}

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    if(!bled_run_dir)
        gtemp_x = 5;
    else
        x = iLED_COL_NUM;
    for(i=0; i<((iLED_COL_NUM+1)/2); i++)
    {
        if(iRGB_QICAI == led_rgb_index)
        {
            rgb_enable = (i&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        gtemp_j = led_to_matrix_tab_3[i+iMATRIX_COL_NUM*0];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[i+iMATRIX_COL_NUM*1];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[i+iMATRIX_COL_NUM*2];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[i+iMATRIX_COL_NUM*3];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[i+iMATRIX_COL_NUM*4];
        rgb_pwm0_w();

        gtemp_j = led_to_matrix_tab_3[iMATRIX_COL_NUM-i+iMATRIX_COL_NUM*0];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[iMATRIX_COL_NUM-i+iMATRIX_COL_NUM*1];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[iMATRIX_COL_NUM-i+iMATRIX_COL_NUM*2];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[iMATRIX_COL_NUM-i+iMATRIX_COL_NUM*3];
        rgb_pwm0_w();
        gtemp_j = led_to_matrix_tab_3[iMATRIX_COL_NUM-i+iMATRIX_COL_NUM*4];
        rgb_pwm0_w();
        if(!bled_run_dir)
            gtemp_x++;
        else
            gtemp_x--;
    }
}

