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
unsigned char       const       led_liuguang_l_r_tbl[]={
    128, 96, 64, 32,  0, 32, 64, 96,128, 96, 64, 32,  0, 32, 64, 96,128, 96, 64, 32,
};
unsigned char       const       led_liuguang_rgb_tbl[]={
      1,  2,  3,  4,  6,  7,  1,  2,  3,  4,  5,  6,  1,  2,  3,  4,  5,  6,  1,  2,
};

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;
void led_mode_liuguang_l_r_w(void)
{
    unsigned char j;

    j = gtemp_i++;     //led_to_matrix_tab_1[gtemp_i++];
    if(br_enable)
        pwm_r_array[j] = gtemp_j;
    else
        pwm_r_array[j] = 0;
    if(bg_enable)
        pwm_g_array[j] = gtemp_j;
    else
        pwm_g_array[j] = 0;
    if(bb_enable)
        pwm_b_array[j] = gtemp_j;
    else
        pwm_b_array[j] = 0;
}

void liuguang_process(void)
{
    unsigned char i, k;
    unsigned int x;

    x = 0x0001;
    for(i=0; i<16; i++)
    {
        if(led_status_reg & x)
        {
            pwm_duty_array_0[i]++;
            if(iPWM_MAX <= pwm_duty_array_0[i])
            {
                led_status_reg &= ~x;
            }
        }
        else
        {
            pwm_duty_array_0[i]--;
            if(0 == pwm_duty_array_0[i])
            {
                pwm_duty_array_1[i]++;
                if(7 < pwm_duty_array_1[i])
                    pwm_duty_array_1[i]=1;
                led_status_reg |= x;
            }
        }
        x <<= 1;
    }

    k = 0x01;
    for(i=16; i<iLED_COL_NUM; i++)
    {
        if(led_status_reg_ex & k)
        {
            pwm_duty_array_0[i]++;
            if(iPWM_MAX <= pwm_duty_array_0[i])
            {
                led_status_reg_ex &= ~k;
            }
        }
        else
        {
            pwm_duty_array_0[i]--;
            if(0 == pwm_duty_array_0[i])
            {
                pwm_duty_array_1[i]++;
                if(7 < pwm_duty_array_1[i])
                    pwm_duty_array_1[i]=1;
                led_status_reg_ex |= k;
            }
        }
        k <<= 1;
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];

    gtemp_i = 0;
    for(k=0; k<iLED_COL_NUM; k++)
    {
        if(bled_run_dir)
        {
            gtemp_j = pwm_duty_array_0[k];
            if(iRGB_QICAI == led_rgb_index)
                rgb_enable = pwm_duty_array_1[k];
        }
        else
        {
            gtemp_j = pwm_duty_array_0[iLED_COL_NUM-1-k];
            if(iRGB_QICAI == led_rgb_index)
                rgb_enable = pwm_duty_array_1[iLED_COL_NUM-1-k];
        }

        led_mode_liuguang_l_r_w();
        led_mode_liuguang_l_r_w();
        led_mode_liuguang_l_r_w();
        led_mode_liuguang_l_r_w();
        led_mode_liuguang_l_r_w();
    }
}

/******************************************************************************
* 函数名称: led_mode_snake
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_liuguang_l_r(void)
{
    if(led_speed_lev>led_delay_count)
    {
		led_delay_count++;
        return;
	}
    led_delay_count = 0;

    liuguang_process();
}
