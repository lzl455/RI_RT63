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
* 函数名称: led_mode_bhqf
* 功能描述: 百花齐放
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_bhqf(void)
{
    unsigned char i;

    if(led_speed_lev>led_delay_count)
    {
        led_delay_count++;
        return;
    }
    led_delay_count = 0;

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(gtemp_i=0; gtemp_i<(iLED_MAX_BHQF/4); gtemp_i++)
    {
        switch(pwm_duty_array_3[gtemp_i])
        {
            case 0:
                pwm_duty_array_1[gtemp_i]++;
                if(iPWM_MAX == pwm_duty_array_1[gtemp_i])
                    pwm_duty_array_3[gtemp_i]++;
                break;
            case 1:
                pwm_duty_array_0[gtemp_i]--;
                if(0 == pwm_duty_array_0[gtemp_i])
                    pwm_duty_array_3[gtemp_i]++;
                break;
            case 2:
                pwm_duty_array_2[gtemp_i]++;
                if(iPWM_MAX == pwm_duty_array_2[gtemp_i])
                    pwm_duty_array_3[gtemp_i]++;
                break;
            case 3:
                pwm_duty_array_1[gtemp_i]--;
                if(0 == pwm_duty_array_1[gtemp_i])
                    pwm_duty_array_3[gtemp_i]++;
                break;
            case 4:
                pwm_duty_array_0[gtemp_i]++;
                if(iPWM_MAX == pwm_duty_array_0[gtemp_i])
                    pwm_duty_array_3[gtemp_i]++;
                break;
            default:
                pwm_duty_array_2[gtemp_i]--;
                if(0 == pwm_duty_array_2[gtemp_i])
                    pwm_duty_array_3[gtemp_i]=0;
                break;
        }
    }

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

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    for(i=0; i<(iLED_MAX_BHQF/4); i++)
    {
        gtemp_x = gtemp_i; //led_to_matrix_tab_1[gtemp_i];

        if(br_enable)
            pwm_r_array[gtemp_x] = pwm_duty_array_0[i];
        else
            pwm_r_array[gtemp_x] = 0;

        if(bg_enable)
            pwm_g_array[gtemp_x] = pwm_duty_array_1[i];
        else
            pwm_g_array[gtemp_x] = 0;

        if(bb_enable)
            pwm_b_array[gtemp_x] = pwm_duty_array_2[i];
        else
            pwm_b_array[gtemp_x] = 0;
        gtemp_i++;
    }
}
