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
void led_mode_arrow(void)
{
    unsigned char i, x, k;

    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

    for(i=0; i<iLED_ROW_NUM; i++)
    {
        if(iLED_COL_NUM <= pwm_duty_array_1[i])
		    pwm_duty_array_1[i] = 0;
        
        k = pwm_duty_array_1[i];
        x = --pwm_duty_array_0[i*iLED_COL_NUM+k];
        
	    if(((iPWM_MAX*5)/6) >= x)
        {
	    	pwm_duty_array_1[i]++;
            if(iLED_COL_NUM<=pwm_duty_array_1[i])
                pwm_duty_array_1[i] = 0;

            pwm_duty_array_0[i*iLED_COL_NUM+k] = ((iPWM_MAX*5)/6);
            k = pwm_duty_array_1[i];
            pwm_duty_array_0[i*iLED_COL_NUM+k] = iPWM_MAX;
        }

	    if(0!=k)
		    k--;
	    else
	        k = (iLED_COL_NUM-1);
	    pwm_duty_array_0[i*iLED_COL_NUM+k] = x-((iPWM_MAX*1)/6);

	    if(0!=k)
		    k--;
	    else
	        k = (iLED_COL_NUM-1);
	    pwm_duty_array_0[i*iLED_COL_NUM+k] = x-((iPWM_MAX*2)/6);

	    if(0!=k)
		    k--;
	    else
	        k = (iLED_COL_NUM-1);
	    pwm_duty_array_0[i*iLED_COL_NUM+k] = x-((iPWM_MAX*3)/6);

	    if(0!=k)
		    k--;
	    else
	        k = (iLED_COL_NUM-1);
	    pwm_duty_array_0[i*iLED_COL_NUM+k] = x-((iPWM_MAX*4)/6);

	    if(0!=k)
		    k--;
	    else
	        k = (iLED_COL_NUM-1);
	    pwm_duty_array_0[i*iLED_COL_NUM+k] = x-((iPWM_MAX*5)/6);
    }

    gtemp_j = 0;
    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(gtemp_x=0; gtemp_x<iLED_NUM_MAX; gtemp_x++)
    {
        if(iRGB_QICAI <= led_rgb_index)
        {
            rgb_enable = (gtemp_x&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        if(!bled_run_dir)
            gtemp_j = led_to_matrix_tab_3[gtemp_x]; 
        else
            gtemp_j = led_to_matrix_tab_4[gtemp_x]; 
        rgb_pwm0_w();
    }
}

