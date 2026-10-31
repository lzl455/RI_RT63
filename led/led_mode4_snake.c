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

unsigned char                   snake_led_index;

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
void led_mode_snake(void)
{
    unsigned char x, y ,k;

    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

	if(!bled_run_dir)
    {
	    if(iLED_NUM_MAX <= snake_led_index)
		    snake_led_index = 0;

	    k = snake_led_index;
	    y = led_snake_table[k];
	    x = --pwm_duty_array_0[y];

	    if(((iPWM_SNAKE_MAX*5)/6)>=x)
        {
	    	snake_led_index++;
            if(iLED_NUM_MAX<=snake_led_index)
                snake_led_index = 0;
            pwm_duty_array_0[y] = ((iPWM_SNAKE_MAX*5)/6);
            y = led_snake_table[snake_led_index];
            pwm_duty_array_0[y] = iPWM_SNAKE_MAX;
        }
	    x = pwm_duty_array_0[led_snake_table[k]];
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_NUM_MAX-1);
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*1)/6);
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_NUM_MAX-1);
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*2)/6);
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_NUM_MAX-1);
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*3)/6);
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_NUM_MAX-1);
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*4)/6);
        
	    if(0!=k)
	    	k--;
	    else
	        k = (iLED_NUM_MAX-1);
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*5)/6);
    }
    else
    {
	    if(iLED_NUM_MAX <= snake_led_index)
		    snake_led_index = iLED_NUM_MAX-1;

	    k = snake_led_index;
	    y = led_snake_table[k];
	    x = --pwm_duty_array_0[y];

	    if(((iPWM_SNAKE_MAX*5)/6)>=x)
        {
	    	snake_led_index--;
            if(iLED_NUM_MAX<=snake_led_index)
		        snake_led_index = iLED_NUM_MAX-1;
            pwm_duty_array_0[y] = ((iPWM_SNAKE_MAX*5)/6);
            y = led_snake_table[snake_led_index];
            pwm_duty_array_0[y] = iPWM_SNAKE_MAX;
        }
	    x = pwm_duty_array_0[led_snake_table[k]];
        
	    k++;
	    if(iLED_NUM_MAX <= k)
	        k = 0;
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*1)/6);
        
	    k++;
	    if(iLED_NUM_MAX <= k)
	        k = 0;
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*2)/6);

	    k++;
	    if(iLED_NUM_MAX <= k)
	        k = 0;
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*3)/6);
        
	    k++;
	    if(iLED_NUM_MAX <= k)
	        k = 0;
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*4)/6);
        
	    k++;
	    if(iLED_NUM_MAX <= k)
	        k = 0;
	    y = led_snake_table[k];
	    pwm_duty_array_0[y] = x-((iPWM_SNAKE_MAX*5)/6);
    }
    
    if(0 == scan_index)
    {
        scan_index= 1;
        gtemp_x = 0;
        gtemp_y = (iLED_NUM_MAX)/2;
    }
    else
    {
        scan_index= 0;
        gtemp_x = (iLED_NUM_MAX)/2;
        gtemp_y = iLED_NUM_MAX;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(; gtemp_x<gtemp_y; gtemp_x++)
    {
        if(iRGB_QICAI <= led_rgb_index)
        {
            rgb_enable = (gtemp_x&0x07);
            if(0==rgb_enable)
                rgb_enable = 4;
        }

        gtemp_j = gtemp_x; //led_to_matrix_tab_1[gtemp_x];
        rgb_pwm0_w();
    }
}
