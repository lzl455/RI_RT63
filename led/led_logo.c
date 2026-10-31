/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include "..\defines.h"

//-----------------------------------------------------------------------------;
// 常量定义区
//

//-----------------------------------------------------------------------------;
// 变量定义区
//
USBD_U16                        uled_ctrl_reg;
USBD_U16                        uled_status_reg;
USBD_U8                         uled_status_reg_ex;

enum led_mod                    led_cur_mode, led_cur_mode_bak;
enum led_mod                    led_pre_mode;
enum speed_level                led_speed_lev;
unsigned char                   led_rgb_index;

unsigned char                   led_scan_count;
unsigned char                   pwm_value;
enum led_level                  led_light_value;

unsigned char                   pwm_time_count;
unsigned char                   led_delay_count;
USBD_U8                         urgb_enable;
unsigned char                   scan_index;
unsigned char                   back_led_off_delay;

unsigned char                   save_6621d_delay;

unsigned int                    mode_swtich_time_count;
unsigned int                    rf_delay_time_count;

unsigned char                   pwm_duty_array_0[0x80];
unsigned char                   pwm_duty_array_1[0x80];
unsigned char                   pwm_duty_array_2[0x80];
unsigned char                   pwm_duty_array_3[0x80];
unsigned int led_hint_time_count;
unsigned char color_index;
unsigned char led_count;
//-----------------------------------------------------------------------------;
// 表格定义区
//
extern void fcc_test_process(void);

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: pwm2_init
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void pwm2_init(void)
{
 //1、时钟源设置
    T1CR = 0x08;                                 // 递增模式，系统高频时钟，1:64分频
    TC1CL = 0X00;                                // 将TC1CL清零    
    TC1CH = 0x00;                                // 将TC1CH清零
    TC1PRH = 0x00;
    TC1PRL = 0x00;
    if(4==led_light_lev)
        TC1PRL = iPWM_MAX;
    else if(3==led_light_lev)
        TC1PRH = 0x01;
    else if(2==led_light_lev)
        TC1PRH = 0x02;
    else //if(1==led_light_lev)
        TC1PRH = 0x05;

//PWM100设置
    PWM100CR = 0x00;
    PWM100DH = 0x00;
    PWM100DL = 0x00;

    PWM101CR = 0x00;
    PWM101DH = 0x00;
    PWM101DL = 0x00;

    PWM102CR = 0x00;
    PWM102DH = 0x00;
    PWM102DL = 0x00;

    PWM103CR = 0x00;
    PWM103DH = 0x00;
    PWM103DL = 0x00;

    PWM104CR = 0x00;
    PWM104DH = 0x00;
    PWM104DL = 0x00;

    PWM105CR = 0x00;
    PWM105DH = 0x00;
    PWM105DL = 0x00;

    PWM106CR = 0x00;
    PWM106DH = 0x00;
    PWM106DL = 0x00;

    PWM107CR = 0x00;
    PWM107DH = 0x00;
    PWM107DL = 0x00;

    PWM108CR = 0x00;
    PWM108DH = 0x00;
    PWM108DL = 0x00;

    PWM109CR = 0x00;
    PWM109DH = 0x00;
    PWM109DL = 0x00;

    PWM110CR = 0x00;
    PWM110DH = 0x00;
    PWM110DL = 0x00;

    PWM111CR = 0x00;
    PWM111DH = 0x00;
    PWM111DL = 0x00;

    PWM112CR = 0x00;
    PWM112DH = 0x00;
    PWM112DL = 0x00;

    PWM113CR = 0x00;
    PWM113DH = 0x00;
    PWM113DL = 0x00;

    PWM114CR = 0x00;
    PWM114DH = 0x00;
    PWM114DL = 0x00;
}

/******************************************************************************
* 函数名称: led_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void device_led_on(void)
{
    // device_led_off();

    // if(!bconn_type_usb)
    // {
        if(iDEVICE_TYPE_BT0 == (sys_ctrl_reg&0x0F))
        {
            pwm_r_array[iKEY_INDEX_BT0] = 0;
            pwm_g_array[iKEY_INDEX_BT0] = 0;
            pwm_b_array[iKEY_INDEX_BT0] = iPWM_MAX;
        }
        // else if(iDEVICE_TYPE_BT1 == (sys_ctrl_reg&0x0F))
        // {
        //     pwm_r_array[iKEY_INDEX_BT1] = iPWM_MAX;
        //     pwm_g_array[iKEY_INDEX_BT1] = iPWM_MAX;
        //     pwm_b_array[iKEY_INDEX_BT1] = iPWM_MAX;
        // }
        // else if(iDEVICE_TYPE_BT2 == (sys_ctrl_reg&0x0F))
        // {
        //     pwm_r_array[iKEY_INDEX_BT2] = iPWM_MAX;
        //     pwm_g_array[iKEY_INDEX_BT2] = iPWM_MAX;
        //     pwm_b_array[iKEY_INDEX_BT2] = iPWM_MAX;
        // }
        else if(iDEVICE_TYPE_24G == (sys_ctrl_reg&0x0F))
        {
            pwm_r_array[iKEY_INDEX_24G] = 0;
            pwm_g_array[iKEY_INDEX_24G] = iPWM_MAX;
            pwm_b_array[iKEY_INDEX_24G] = 0;
        }
    // }
    // else
    // {
    //     pwm_r_array[iKEY_INDEX_USB] = 0;
    //     pwm_g_array[iKEY_INDEX_USB] = 0;
    //     pwm_b_array[iKEY_INDEX_USB] = 0;
    // }
}

void device_led_off(void)
{
    pwm_r_array[iKEY_INDEX_BT0] = 0;
    pwm_g_array[iKEY_INDEX_BT0] = 0;
    pwm_b_array[iKEY_INDEX_BT0] = 0;

    pwm_r_array[iKEY_INDEX_BT1] = 0;
    pwm_g_array[iKEY_INDEX_BT1] = 0;
    pwm_b_array[iKEY_INDEX_BT1] = 0;

    pwm_r_array[iKEY_INDEX_BT2] = 0;
    pwm_g_array[iKEY_INDEX_BT2] = 0;
    pwm_b_array[iKEY_INDEX_BT2] = 0;

    pwm_r_array[iKEY_INDEX_24G] = 0;
    pwm_g_array[iKEY_INDEX_24G] = 0;
    pwm_b_array[iKEY_INDEX_24G] = 0;

    pwm_r_array[iKEY_INDEX_USB] = 0;
    pwm_g_array[iKEY_INDEX_USB] = 0;
    pwm_b_array[iKEY_INDEX_USB] = 0;
}

/*void clr_all_rgb(void)
{
    memset(pwm_r_array, 0x00, 128);
    memset(pwm_g_array, 0x00, 128);
    memset(pwm_b_array, 0x00, 128);
}*/

void clr_rgb(void)
{
    memset(pwm_r_array, 0x00, iLED_NUM_MAX);
    memset(pwm_g_array, 0x00, iLED_NUM_MAX);
    memset(pwm_b_array, 0x00, iLED_NUM_MAX);
}

void set_rgb(void)
{
    memset(pwm_r_array, iPWM_MAX, iLED_NUM_MAX);
    memset(pwm_g_array, iPWM_MAX, iLED_NUM_MAX);
    memset(pwm_b_array, iPWM_MAX, iLED_NUM_MAX);
}

void led_hint(void)
{
    for(unsigned char i=0; i<3; i++)
    {
        set_rgb();
        delayms(50);
        clr_rgb();
        delayms(50);
    }
}

void rgb_pwm012_w(void)
{
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

void rgb_pwm0_w(void)
{
     if(br_enable)
         pwm_r_array[gtemp_j] = pwm_duty_array_0[gtemp_x];
     else
         pwm_r_array[gtemp_j] = 0;
     if(bg_enable)
         pwm_g_array[gtemp_j] = pwm_duty_array_0[gtemp_x];
     else
         pwm_g_array[gtemp_j] = 0;
     if(bb_enable)
         pwm_b_array[gtemp_j] = pwm_duty_array_0[gtemp_x];
     else
         pwm_b_array[gtemp_j] = 0;          
}

void rgb_w_max(void)
{
    if(br_enable)
        pwm_r_array[gtemp_j] = iPWM_MAX;
    else
        pwm_r_array[gtemp_j] = 0;
    if(bg_enable)
        pwm_g_array[gtemp_j] = iPWM_MAX;
    else
        pwm_g_array[gtemp_j] = 0;
    if(bb_enable)
        pwm_b_array[gtemp_j] = iPWM_MAX;
    else
        pwm_b_array[gtemp_j] = 0;
}

void led_set_color(unsigned char r, unsigned char g, unsigned char b)
{
    memset(pwm_r_array, r, iLED_NUM_MAX);
    memset(pwm_g_array, g, iLED_NUM_MAX);
    memset(pwm_b_array, b, iLED_NUM_MAX);
}

/******************************************************************************
* 函数名称: led_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_process(void)
{
    unsigned char i;

    if(bsave_flash)
    {
        cfg_mode_save();
        bsave_flash = 0;
    }

    if(bsave_6621d)
    {
        if(250 <= save_6621d_delay)
        {
            if(iUART_TX_IDLE==cmd_tx_index)
            {
                cfg_6621d_save();
                bsave_6621d = 0;
            }
        }
        else
            save_6621d_delay++;
    }

    if(bmode_swtich_hint)
    {
        if(iDEVICE_TYPE_USB == (sys_ctrl_reg&0x0F))
        {
            bmode_swtich_hint = 0;
            return;
        }
            
        mode_swtich_time_count++;
        if(3 > mode_swtich_time_count)
        {
            b24g_bt_conn_ok = 1;
            clr_all_rgb();
        }
        else if(iMODE_HINT_TIME > mode_swtich_time_count)
        {
            device_led_on();
        }        
        else
        {
            bmode_swtich_hint = 0;
            device_led_off();
        }
        return;
    }
/* 
    if(bwin_mac_hint)
    {
        if(5>delay_time_count)
        {
            led_light_value = iLED_LEV_MAX;
            clr_rgb();
        }

        if(iMODE_HINT_TIME > delay_time_count)
        {
            if(bwin_mac_sataus)
            {
                pwm_r_array[iKEY_INDEX_WIN] = iPWM_MAX;
                pwm_g_array[iKEY_INDEX_WIN] = iPWM_MAX;
                pwm_b_array[iKEY_INDEX_WIN] = iPWM_MAX;
            }
            else
            {
                pwm_r_array[iKEY_INDEX_MAC] = iPWM_MAX;
                pwm_g_array[iKEY_INDEX_MAC] = iPWM_MAX;
                pwm_b_array[iKEY_INDEX_MAC] = iPWM_MAX;
            }
            delay_time_count++;
        }
        else
        {
            bwin_mac_hint = 0;
            led_light_value = led_light_lev;
            led_pre_mode = iMODE_LED_INVALID;
        }
        return;
    }
 */
    if(!bconn_type_usb)
    {
        if(bom6621d_conning)
        {
            if(0 == device_conn_index)
            {
                clr_all_rgb();
                device_led_off();

                device_conn_index++;
                rf_delay_time_count = 0;
            }
            else if(1 == device_conn_index)
            {
                if(bom6621d_conn_ok)
                {
                    rf_delay_time_count = 0;
                    device_conn_index++;
                }
                rf_delay_time_count++;
                if(0 != (rf_delay_time_count&0x40))
                {
                    device_led_on();
                }
                else
                {
                    device_led_off();
                }

                fcc_test_process();

                if(iCONN_HOLD_TIME < rf_delay_time_count)
                {
                    bom6621d_conning = 0;
                    bdevice_conn = 0;
                    device_led_off();

                    led_pre_mode = iMODE_LED_INVALID;
                }
            }
            else //if(2 == device_conn_index)
            {
                rf_delay_time_count++;
                if(iCONN_OK_TIME > rf_delay_time_count)
                {
                    device_led_on();
                }
                else
                {
                    bom6621d_conning = 0;
                    bom6621d_conn_ok = 1;
                    b24g_bt_conn_ok = 0;
                    bdevice_conn = 0;
                    device_led_off();
                    led_pre_mode = iMODE_LED_INVALID;
                }
            }
            return;
        }

        if(!bom6621d_conn_ok)
        {                                           // RF 断连
            if((250 < back_led_off_delay) || !bled_hint_ing)
            {
                if(b24g_bt_conn_ok)
                {
                    b24g_bt_conn_ok = 0;
                    rf_delay_time_count = 0;

                    bcaps_lock = 0;
                    clr_all_rgb();
                }
                else
                {
                    if(bom6621d_disconn_sleep)
                    {
                        device_led_off();
                        pwm2_init();
                        sleep_time = (iWORK_2MIN_TIME+1);
                    }
                    else
                    {
                        rf_delay_time_count++;
                        if(0 != (rf_delay_time_count&0x100))
                        {
                            if(0 == (rf_delay_time_count&0x007F))
                            {
                                if(!bkb_tx_busy)
                                    bstd_data_send = 1;
                            }
                            device_led_on();
                        }
                        else
                        {
                            device_led_off();
                        }
                    }
                }
                return;
            }
            else
            {
                back_led_off_delay++;
            }
        }
        else
        {
            if(!b24g_bt_conn_ok)
            {
                b24g_bt_conn_ok = 1;
                back_led_off_delay = 0;

                if(!bled_hint_ing)
                {
                    device_led_off();
                    led_pre_mode = iMODE_LED_INVALID;
                }
                bled_hint_ing = 0;
            }
        }
    }
    else
    {
        if(busb_suspend_en || !bep1_ep2_enable)
        {
            if(bled_hint_ing)
            {
                if(250 < back_led_off_delay)
                {
                    busb_suspend_bak = 1;

                    bled_hint_ing = 0;
                    bcaps_lock = 0;
                    clr_all_rgb();
                    return;
                }
                back_led_off_delay++;
            }
            else
            {
                return;
            }
        }
        else
        {
            if(busb_suspend_bak)
            {
                busb_suspend_bak = 0;

                back_led_off_delay = 0;
                led_pre_mode = iMODE_LED_INVALID;
            }
        }
    }

    if(!buart_flash_ok || (0==led_light_lev) ||!bled_bright_en)
    {
        if(!buart_flash_ok && !bom6621d_flash_r)
        {
            bom6621d_flash_r = 1;
        }
        clr_rgb();
        return;
    }

    if(led_pre_mode != led_cur_mode)
    {
        led_pre_mode = led_cur_mode;

        led_delay_count = 0;
        bled_mode_single = 0;

        clr_rgb();
        memset(pwm_duty_array_0, 0x00, iLED_MAX);
        memset(pwm_duty_array_1, 0x00, iLED_MAX);
        memset(pwm_duty_array_2, 0x00, iLED_MAX);
        memset(pwm_duty_array_3, 0x00, iLED_MAX);

        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:

                break;
            case iMODE_LED_ON:

                break;
            case iMODE_LED_BREATH:
                pwm_time_count = 0;
                led_delay_count = 0xFF;
                rgb_enable = rgb_en_tbl[led_rgb_index&0x0F];

                break;
            case iMODE_LED_SNAKE:
                snake_led_index = 5;
                // pwm_duty_array_0[5] = ((iPWM_MAX*6)/6);

                break;
            case iMODE_LED_NHJB:
                nhjb_led_index = 0;
                pwm_duty_array_0[0] = iPWM_MAX;
                pwm_duty_array_0[1] = 0x00;
                pwm_duty_array_0[2] = 0x00;

                break;
            case iMODE_LED_SINGLE:
                bled_mode_single = 1;
                for(i=0; i<iMATRIX_NUM_MAX; i++)
                {
                    pwm_duty_array_0[i] = iPWM_MAX;
                    pwm_duty_array_1[i] = (i&0x0F);
                    if(0==pwm_duty_array_1[i])
                        pwm_duty_array_1[i] = 1;
                }

                break;
            case iMODE_LED_LG_L_R:
                led_status_reg = 0xF0F0;
                led_status_reg_ex = 0;

                memcpy_const(pwm_duty_array_0, led_liuguang_l_r_tbl, iLED_COL_NUM);
                memcpy_const(pwm_duty_array_1, led_liuguang_rgb_tbl, iLED_COL_NUM);

                break;
            case iMODE_LED_LXGY:
                memcpy_const(pwm_duty_array_0, lxgy_r_tbl, iMATRIX_ROW_NUM);
                memcpy_const(pwm_duty_array_1, lxgy_g_tbl, iMATRIX_ROW_NUM);
                memcpy_const(pwm_duty_array_2, lxgy_b_tbl, iMATRIX_ROW_NUM);
                memcpy_const(pwm_duty_array_3, lxgy_ctrl_tbl, iMATRIX_ROW_NUM);

                break;
            case iMODE_LED_STAR:
                snake_led_index = 0xFF;
                lfsr_value = 0x55AA;
                break;
            case iMODE_LED_SBZL:
                for(i=0; i<iLED_COL_NUM; i++)
                {
                    pwm_duty_array_0[i] = sbzl_r_tbl[iLED_COL_NUM-1-i];
                    pwm_duty_array_1[i] = sbzl_g_tbl[iLED_COL_NUM-1-i];
                    pwm_duty_array_2[i] = sbzl_b_tbl[iLED_COL_NUM-1-i];
                    pwm_duty_array_3[i] = sbzl_ctrl_tbl[iLED_COL_NUM-1-i];
                }

                break; 
            case iMODE_LED_ZXB:
                led_status_reg = 0;
                bled0_status = 1;

                break; 
            case iMODE_LED_YZMB:

                break;
            case iMODE_LED_CHLP:
                memcpy_const(pwm_duty_array_0, chlp_r_tbl, iLED_COL_NUM*2);
                memcpy_const(pwm_duty_array_1, chlp_g_tbl, iLED_COL_NUM*2);
                memcpy_const(pwm_duty_array_2, chlp_b_tbl, iLED_COL_NUM*2);
                memcpy_const(pwm_duty_array_3, chlp_ctrl_tbl, iLED_COL_NUM*2);

                break; 
            case iMODE_LED_BHQF:
                pwm_duty_array_0[0] = 20;
                pwm_duty_array_1[0] = 80;
                pwm_duty_array_2[0] = 120;
                for(i=1; i<(iLED_MAX_BHQF/4); i++)
                {
                    pwm_duty_array_0[i] = (pwm_duty_array_0[i-1]+(i<<4)+10);
                    if(iPWM_MAX < pwm_duty_array_0[i])
                        pwm_duty_array_0[i] -= iPWM_MAX;
                    pwm_duty_array_1[i] = (pwm_duty_array_1[i-1]+(i<<4)+30);
                    if(iPWM_MAX < pwm_duty_array_1[i])
                        pwm_duty_array_1[i] -= iPWM_MAX;
                    pwm_duty_array_2[i] = (pwm_duty_array_2[i-1]+(i<<4)+50);
                    if(iPWM_MAX < pwm_duty_array_2[i])
                        pwm_duty_array_2[i] -= iPWM_MAX;

                    pwm_duty_array_3[i] = (i&0x07);
                    if(5 < pwm_duty_array_3[i])
                        pwm_duty_array_3[i] -= 5;
                }
                break; 
            case iMODE_LED_ARROW:
                pwm_duty_array_1[0] = 5;
                pwm_duty_array_0[0*iLED_COL_NUM+5] = ((iPWM_MAX*6)/6);
                pwm_duty_array_1[1] = 6;
                pwm_duty_array_0[1*iLED_COL_NUM+6] = ((iPWM_MAX*6)/6);
                pwm_duty_array_1[2] = 7;
                pwm_duty_array_0[2*iLED_COL_NUM+7] = ((iPWM_MAX*6)/6);
                pwm_duty_array_1[3] = 6;
                pwm_duty_array_0[3*iLED_COL_NUM+6] = ((iPWM_MAX*6)/6);
                pwm_duty_array_1[4] = 5;
                pwm_duty_array_0[4*iLED_COL_NUM+5] = ((iPWM_MAX*6)/6);
                break; 
            case iMODE_LED_CENTRE:
                snake_led_index = 5;
                pwm_duty_array_0[5] = ((iPWM_MAX*6)/6);

                break;
            case iMODE_LED_DEF:

                break; 
            case iMODE_LED_RED:
                break;
            case iMODE_LED_GREEN:
                break;
            case iMODE_LED_BLUE:
                break;
        }
    }
    else
    {
        bled_hint_ing = 1;
        switch(led_cur_mode)
        {
            case iMODE_LED_OFF:
                break;
            case iMODE_LED_ON:
                rgb_enable = rgb_en_tbl[led_rgb_index&0x07];
                for(gtemp_j=0; gtemp_j<iLED_NUM_MAX; gtemp_j++)
                {
                    if(iRGB_QICAI <= led_rgb_index)
                        rgb_enable = rgb_en_tbl[gtemp_j&0x07];
                    rgb_w_max();
                }
                break;
            case iMODE_LED_BREATH:
                led_mode_breath();
                break;
            case iMODE_LED_SNAKE:
                led_mode_snake();
                break;
            case iMODE_LED_NHJB:
                led_mode_nhjb();
                break;
            case iMODE_LED_SINGLE:
                led_mode_single();
                break;
            case iMODE_LED_LG_L_R:
                led_mode_liuguang_l_r();
                break;
            case iMODE_LED_LXGY:
                led_mode_lxgy();
                break;
            case iMODE_LED_STAR:
                led_mode_star();
                break;
            case iMODE_LED_SBZL:
                led_mode_sbzl();
                break;
            case iMODE_LED_ZXB:
                led_mode_zxb();
                break;
            case iMODE_LED_YZMB:
                led_mode_yzmb();
                break; 
            case iMODE_LED_CHLP:
                led_mode_chlp();
                break;
            case iMODE_LED_BHQF:
                led_mode_bhqf();
                break;
            case iMODE_LED_ARROW:
                led_mode_arrow();
                break;
            case iMODE_LED_CENTRE:
                led_mode_centre();
                break;
            case iMODE_LED_DEF:
                led_mode_def();
                break;
            case iMODE_LED_RED:
                led_set_color(iPWM_MAX, 0, 0);
                break;
            case iMODE_LED_GREEN:
                led_set_color(0, iPWM_MAX, 0);
                break;
            case iMODE_LED_BLUE:
                led_set_color(0, 0, iPWM_MAX);
                break;
        }
    }
}

/******************************************************************************
* 函数名称: timer_int_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void timer_int_process(void)
{
    if(iMATRIX_COL_NUM>led_scan_count)
    {
        if((~MATRX_R&0x7C) == matrix_status_bak[led_scan_count])
            matrix_status[led_scan_count] = (~MATRX_R&0x7C);
        else
            matrix_status_bak[led_scan_count] = (~MATRX_R&0x7C);
    }

    if(++SwBusTimer>=60)    //判定间隔时间
    {
        SwBusTimer = 0;

        if(IOFICR&0X03)        //一定时间后F0、F1电平未翻转认定总线进入挂起状态
        {
            //if(USBEnumState==USBE_Configured)
            {
                if(!busb_suspend_en_bak)
                {
                    if((IOF0==1)&&(IOF1==0)) //全速模式挂起时为J状态
                    {
                        busb_suspend_en_bak = 1;
                        busb_suspend_en = 1;
                    }
                }
            }
        }
        else
        {
            IOFICR |= 0X03;        //F0、F1中断关闭后一定时间后再开启中断检测电平
            IOFCHIF = 0;
        }
    }

    led_scan_count++;
    if(iMATRIX_COL_NUM<=led_scan_count)
    {
        led_scan_count = 0;
        led_index_value = 0;
        bkey_scan = 1;

        sof_count++;
        if(0 == (sof_count&0x03))
        {                                    // 周期13.2ms
            conn_time_count++;
            sleep_time++;
            if(blvd_status)
                low_hint_time++;
            if(0 != power_on_time)
                power_on_time--;
        }

        int_iod_dat = 0x7F;
        int_ioe_dat = 0x7F;
        uart_tx_delay++;
        uart_rx_delay++;
        if(2 < uart_rx_delay)
            rx_r_index = 0;
    }

    IOE |= 0x7F;
    IOB = 0xFF;
    IOC = 0xFF;
    IOD = 0xFF;

    PWM114CR = 0x00;
    PWM100CR = 0x00;
    PWM101CR = 0x00;
    PWM102CR = 0x00;
    PWM103CR = 0x00;
    PWM104CR = 0x00;
    PWM105CR = 0x00;
    PWM106CR = 0x00;
    PWM107CR = 0x00;
    PWM108CR = 0x00;
    PWM109CR = 0x00;
    PWM110CR = 0x00;
    PWM111CR = 0x00;
    PWM112CR = 0x00;
    PWM113CR = 0x00;
    T1CR = 0x00;

#asm
    bankbsr 0x0E

    ldfsr   2, _pwm_r_array
    movr    _led_index_value, w, c
    addar   0xD9, f, c
    movrr   POSTINC2, _PWM112DL
    movrr   POSTINC2, _PWM109DL
    movrr   POSTINC2, _PWM106DL
    movrr   POSTINC2, _PWM103DL
    movrr   POSTINC2, _PWM100DL

    ldfsr   2, _pwm_g_array
    movr    _led_index_value, w, c
    addar   0xD9, f, c
    movrr   POSTINC2, _PWM114DL
    movrr   POSTINC2, _PWM111DL
    movrr   POSTINC2, _PWM108DL
    movrr   POSTINC2, _PWM105DL
    movrr   POSTINC2, _PWM102DL

    ldfsr   2, _pwm_b_array
    movr    _led_index_value, w, c
    addar   0xD9, f, c
    movrr   POSTINC2, _PWM113DL
    movrr   POSTINC2, _PWM110DL
    movrr   POSTINC2, _PWM107DL
    movrr   POSTINC2, _PWM104DL
    movrr   POSTINC2, _PWM101DL
#endasm

    if(0==led_scan_count)
    {
        if(bcaps_lock)
        {
            PWM_R_2 = iPWM_MAX;
            PWM_G_2 = iPWM_MAX;
            PWM_B_2 = iPWM_MAX;
        }
    }else if(1==led_scan_count)
    {
        if(bwin_lock_status&&bwin_mac_sataus&&bled_hint_ing)
        {
            PWM_R_4 = iPWM_MAX;
            PWM_G_4 = iPWM_MAX;
            PWM_B_4 = iPWM_MAX;
        }
        if(bbat_hint_en)
        {
            PWM_R_0 = bat_r_value;
            PWM_G_0 = bat_g_value;
            PWM_B_0 = bat_b_value;
        }
    }

    if(bbat_press_bak&&!(iDEVICE_TYPE_USB == (sys_ctrl_reg&0x0F)))
    {
        led_hint_time_count++;
        if(led_hint_time_count<100)
        {
            // 颜色查找表：低电量(红) | 中电量(黄) | 高电量(绿)
            static const struct
            {
                unsigned char red;
                unsigned char green;
                unsigned char blue;
            } color_table[] = {
                {iPWM_MAX, 0, 0},        // 0-30%
                {iPWM_MAX, iPWM_MAX, 0}, // 40-60%
                {0, iPWM_MAX, 0}         // 70-100%
            };

            color_index = (bat_value_ble <= 30) ? 0 : (bat_value_ble <= 60) ? 1: 2;

            led_count = bat_value_ble / 20;

            if (led_scan_count <= led_count && led_scan_count >= 1 && led_scan_count <= 5)
            {
                PWM_R_0 = color_table[color_index].red;
                PWM_G_0 = color_table[color_index].green;
                PWM_B_0 = color_table[color_index].blue;
            }
        }
        else if(led_hint_time_count == 100)
        {
            led_hint_time_count =0;
            bbat_press_bak=0;
            led_cur_mode =led_cur_mode_bak;
        }   
    }

    TC1CL = 0X00;
    TC1CH = 0x00;

    mPWM_POWER_ON;

    PWM114CR = 0xE0;
    PWM100CR = 0xE0;
    PWM101CR = 0xE0;
    PWM102CR = 0xE0;
    PWM103CR = 0xE0;
    PWM104CR = 0xE0;
    PWM105CR = 0xE0;
    PWM106CR = 0xE0;
    PWM107CR = 0xE0;
    PWM108CR = 0xE0;
    PWM109CR = 0xE0;
    PWM110CR = 0xE0;
    PWM111CR = 0xE0;
    PWM112CR = 0xE0;
    PWM113CR = 0xE0;
    T1CR = 0x88;
#asm
    movia   5
    ADDAR    _led_index_value, f, c
#endasm

    if(8 > led_scan_count)
    {
#asm
        rlncr   _int_iod_dat, f, c
#endasm
        IOD = int_iod_dat;
    }
    else if(14 == led_scan_count)
    {
        PWM_C14_LOW;
    }
    else
	{
#asm
        rlncr   _int_ioe_dat, f, c
#endasm
        IOE = int_ioe_dat;
    }
}
