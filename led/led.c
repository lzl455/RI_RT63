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
USBD_U16                        uhint_led_status;

unsigned char                   bat_r_value;
unsigned char                   bat_g_value;
unsigned char                   bat_b_value;

unsigned char                   lvd_hint_time_count;
unsigned int                    charge_ok_time_count;
unsigned int                    power_off_time_count;
unsigned char                   charge_time_count;

//-----------------------------------------------------------------------------;
// 表格定义区
//

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: led_hint_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void led_hint_process(void)
{
    // LED_CAPS_PIN = !bcaps_lock;

    if(bcharge_ing != USB_5V_PIN)
    {
        bcharge_ing = USB_5V_PIN;
        charge_time_count = 0;
    }

    bcharge_ok = CHARGE_OK_PIN;

    if(!bcharge_ing)
    {                                      // 放电状态
        if(iBAT_POWER_LOW > bat_value_ble)
        {
            if(!blvd_status)
            {                                   // 低压提示
                blvd_status = 1;
                lvd_hint_time_count = 0;
    		    power_off_time_count = 0;
            }
            lvd_hint_time_count++;
            bat_g_value = 0;
            bat_b_value = 0;
            if(low_hint_time<iKB_LOW_10S_TIME)
            {
                if(0==(lvd_hint_time_count&0xC0))
                    bat_r_value = iPWM_MAX;
                else
                    bat_r_value = 0;
            }
            else
                bat_r_value = 0;
            
            bbat_hint_en = 1;

            if(iBAT_POWER_OFF < bat_value_ble)
    		    return;

            power_off_time_count++;
            if(2000 > power_off_time_count)
                return;

            in_sleep_init();
    		off_bt_module();
            while(1)
            {
                IOD = 0x00;
                IOE = 0x40;
                IOACHIF = 0;
                IOFCHIF = 0;
                IOACHIE = 1;
        	    IOFCHIE = 0;

                STPH = 1;
                STPL = 1;
                STOP = 1;
                nop;
                IOACHIF = 0;
                IOFCHIF = 0;
                uart_init();
    
                delayms(1);
                uart_invalid();
                delayms(10);

                get_bat_value();
                if((5 <= bat_value_ble) || USB_5V_PIN)
                    break;                      // 电量大于10%
    
    		    off_bt_module();
                IOD = 0xBF;
                IOE = 0xFF;
    			mPWM_POWER_ON;

                for(gtemp_i=0; gtemp_i<250; gtemp_i++)
    			{
					PWM_R_4_PIN = 0;
    				delayus(250);
					PWM_R_4_PIN = 1;
    				delayms(2);
    			}

    			mPWM_POWER_OFF;
            }

            out_sleep_init();
            cmd_tx_init();

            bom6621d_conn_ok = 0;
            bdevice_conn = 0;
            bom6621d_conning = 0;

            device_type = device_type_bak;
            bdevice_switch = 1;
            cmd_tx_init();
            blvd_status = 0;
        }
        else
        {
            blvd_status = 0;
            bbat_hint_en = 0;
            bat_r_value = 0;
            bat_g_value = 0;
            bat_b_value = 0;
        }
    }
    else
    {
        blvd_status = 0;
        bbat_hint_en = 1;
        if(!bcharge_ok && !bbat_check_err)
        {
		    charge_ok_time_count = 0;
chargeing_hint_process:
            bat_r_value = iPWM_MAX;
            bat_g_value = 0;
            bat_b_value = 0;
        }
        else
        {
		    if(10000>charge_ok_time_count)
			{
			    charge_ok_time_count++;
			    goto chargeing_hint_process;
			}

            blvd_breath_status = 0;
            bat_r_value = 0;
            bat_g_value = iPWM_MAX;
            bat_b_value = 0;
        }
    }
}

