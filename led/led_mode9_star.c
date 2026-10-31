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

#define iLFSR_MULTINOMIAL       0xF521

unsigned int                    lfsr_value;
unsigned char                   start_dec_count;

//-----------------------------------------------------------------------------;
// 表格定义区
//
unsigned char       const   start_dec_delay[8]={
    4,
    8,
    13,
    20,
    30,
    30,
    30,
    30,
};

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
void led_mode_star(void)
{
    unsigned char i, j;
    
    led_delay_count++;
    i = start_dec_delay[led_speed_lev&0x07];
    if(i > led_delay_count)
    {
        start_dec_count++;
        if((led_speed_lev<<1)>start_dec_count)
        {
            start_dec_count++;
            return;
        }
        start_dec_count = 0;

        rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
		if(bw_enable)
			rgb_enable |= (iPWM_R|iPWM_G|iPWM_B);

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

        for(; gtemp_x<gtemp_y; gtemp_x++)
        {
            gtemp_j = gtemp_x; //led_to_matrix_tab_1[gtemp_x];
            if(0 != pwm_duty_array_0[gtemp_x])
            {
                pwm_duty_array_0[gtemp_x]--;

                if(iRGB_QICAI <= led_rgb_index)
                    rgb_enable = (pwm_duty_array_1[gtemp_x]&0x0F);

                rgb_pwm0_w();
            }
            else
            {
                pwm_r_array[gtemp_j] = 0;
                pwm_g_array[gtemp_j] = 0;
                pwm_b_array[gtemp_j] = 0;
            }
        }
        
        return;
    }

    led_delay_count = 0;

    lfsr_value = lfsr_value>>1;
    if(lfsr_value & 0x01)
        lfsr_value ^= iLFSR_MULTINOMIAL;

    j = ((lfsr_value+(lfsr_value>>8))&0x7F);
    if(iLED_MAX <= j)
        j -= iLED_MAX;

    pwm_duty_array_0[j] = iPWM_MAX;
    pwm_duty_array_1[j] = ((lfsr_value>>8)&0x0F);
    if(0==pwm_duty_array_1[j])
        pwm_duty_array_1[j] = 1;
}

