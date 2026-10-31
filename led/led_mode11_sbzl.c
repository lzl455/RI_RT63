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
extern void liuguang_process(void);

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
void led_mode_sbzl(void)
{
    unsigned char k;

    if(led_speed_lev > led_delay_count)
    {
        led_delay_count++;
        return;
    }
    led_delay_count = 0;

    for(gtemp_x=0; gtemp_x<iLED_COL_NUM; gtemp_x++)
    {
        if(0 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_0[gtemp_x]--;
            pwm_duty_array_1[gtemp_x]=iPWM_MAX-pwm_duty_array_0[gtemp_x];
            if(0 == pwm_duty_array_0[gtemp_x])
                pwm_duty_array_3[gtemp_x]++;
        }
        else if(1 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_1[gtemp_x]--;
            pwm_duty_array_2[gtemp_x]=iPWM_MAX-pwm_duty_array_1[gtemp_x];
            if(0 == pwm_duty_array_1[gtemp_x])
                pwm_duty_array_3[gtemp_x]++;
        }
        else //if(2 == pwm_duty_array_3[gtemp_x])
        {
            pwm_duty_array_2[gtemp_x]--;
            pwm_duty_array_0[gtemp_x]=iPWM_MAX-pwm_duty_array_2[gtemp_x];
            if(0 == pwm_duty_array_2[gtemp_x])
                pwm_duty_array_3[gtemp_x]=0;
        }
    }

    if(0 == scan_index)
    {
        scan_index= 1;
        gtemp_i = 0;
        gtemp_x = 0;
        gtemp_y = (iLED_COL_NUM)/2;
    }
    else
    {
        scan_index= 0;
        gtemp_x = (iLED_COL_NUM)/2;
        gtemp_y = iLED_COL_NUM;
        gtemp_i = gtemp_x*iLED_ROW_NUM;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    if(!bled_run_dir)
    {
        for(; gtemp_x<gtemp_y; gtemp_x++)
        {
            for(k=0; k<iLED_ROW_NUM; k++)
            {
                gtemp_j = gtemp_i;
				gtemp_i++;
                if(br_enable)
                    pwm_r_array[gtemp_j] = pwm_duty_array_0[gtemp_x];
                else
                    pwm_r_array[gtemp_j] = 0;
                if(bg_enable)
                    pwm_g_array[gtemp_j] = pwm_duty_array_1[gtemp_x];
                else
                    pwm_g_array[gtemp_j] = 0;
                if(bb_enable)
                    pwm_b_array[gtemp_j] = pwm_duty_array_2[gtemp_x];
                else
                    pwm_b_array[gtemp_j] = 0;
            }
        }
    }
    else
    {
        for(; gtemp_x<gtemp_y; gtemp_x++)
        {
            for(k=0; k<iLED_ROW_NUM; k++)
            {
                gtemp_j = gtemp_i;
				gtemp_i++;
                if(br_enable)
                    pwm_r_array[gtemp_j] = pwm_duty_array_0[iLED_COL_NUM-1-gtemp_x];
                else
                    pwm_r_array[gtemp_j] = 0;
                if(bg_enable)
                    pwm_g_array[gtemp_j] = pwm_duty_array_1[iLED_COL_NUM-1-gtemp_x];
                else
                    pwm_g_array[gtemp_j] = 0;
                if(bb_enable)
                    pwm_b_array[gtemp_j] = pwm_duty_array_2[iLED_COL_NUM-1-gtemp_x];
                else
                    pwm_b_array[gtemp_j] = 0;
            }
        }
    }
}

