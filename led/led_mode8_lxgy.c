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

unsigned char       const   lxgy_r_tbl[6]={
    128,  64,  0,128,  0, 64,
};
unsigned char       const   lxgy_g_tbl[6]={
      0,  64,128, 64,  0,  0,
};
unsigned char       const   lxgy_b_tbl[6]={
      0,   0,  0, 64,128, 64,
};
unsigned char       const   lxgy_ctrl_tbl[6]={
      0,   0,  1,  1,  2,  2,
};

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: 流星赶月
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void led_mode_lxgy(void)
{
    unsigned char i, j, k, x;

    if(led_speed_lev>led_delay_count)
    {
        led_delay_count++;
        return;
    }
    led_delay_count = 0;

    for(i=0; i<iLED_ROW_NUM; i++)
    {
        if(0 == pwm_duty_array_3[i])
        {
            pwm_duty_array_0[i]--;
            pwm_duty_array_1[i]=128-pwm_duty_array_0[i];
            if(0 == pwm_duty_array_0[i])
                pwm_duty_array_3[i]++;
        }
        else if(1 == pwm_duty_array_3[i])
        {
            pwm_duty_array_1[i]--;
            pwm_duty_array_2[i]=128-pwm_duty_array_1[i];
            if(0 == pwm_duty_array_1[i])
                pwm_duty_array_3[i]++;
        }
        else //if(2 == pwm_duty_array_3[i])
        {
            pwm_duty_array_2[i]--;
            pwm_duty_array_0[i]=128-pwm_duty_array_2[i];
            if(0 == pwm_duty_array_2[i])
                pwm_duty_array_3[i]=0;
        }
    }

    rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];
    gtemp_i = 0;
    for(i=0; i<iLED_ROW_NUM; i++)
    {
        if(!bled_run_dir)
			x = i;
        else
			x = (iLED_ROW_NUM-1-i);
        gtemp_j = pwm_duty_array_0[x];
        gtemp_x = pwm_duty_array_1[x];
        gtemp_y = pwm_duty_array_2[x];

        for(k=0; k<iLED_COL_NUM; k++)
        {
            j = led_to_matrix_tab_3[gtemp_i++];
            if(br_enable)
                pwm_r_array[j] = gtemp_j;
            else
                pwm_r_array[j] = 0;
            if(bg_enable)
                pwm_g_array[j] = gtemp_x;
            else
                pwm_g_array[j] = 0;
            if(bb_enable)
                pwm_b_array[j] = gtemp_y;
            else
                pwm_b_array[j] = 0;
        }
    }
}
