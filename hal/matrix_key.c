/*******************************************************************************
* Copyright (c) 2012, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: matrix_key.c
* 文件描述: 矩阵处理程序
*
*******************************************************************************/
#include "..\defines.h"

//----------------------------------------------------------------------------;
//常量定义
//
extern void key_decode(void);
void mode_swtich(unsigned char delay_en);
//----------------------------------------------------------------------------;
//变量定义
//
USBD_U16                        ukey_ctrl;
USBD_U16                        ukey_ctrl_ex;

USBD_U8                         ukey_temp_flag;
USBD_U8                         ukey_temp_flag_1;
//{
    #define key_temp_flag_1     ukey_temp_flag_1.u8

    #define bkey_temp15         ukey_temp_flag_1.BIT.b7
    #define bkey_temp14         ukey_temp_flag_1.BIT.b6
    #define bkey_temp13         ukey_temp_flag_1.BIT.b5
    #define bkey_temp12         ukey_temp_flag_1.BIT.b4
    #define bkey_temp11         ukey_temp_flag_1.BIT.b3
    #define bkey_temp10         ukey_temp_flag_1.BIT.b2
//}
USBD_U8                         ukey_temp_delay;
USBD_U8                         udevice_key;
USBD_U8                         udevice_key_bak;

//unsigned char                   std_key_count;  // 按下按键的个数
unsigned char                   matrix_status[iMATRIX_COL_NUM+1];
unsigned char                   key_fn_status[iMATRIX_NUM_MAX];

unsigned char                   mouse_data_key;
unsigned int                    mouse_data_x;
unsigned int                    mouse_data_y;
unsigned char                   mouse_data_z;

unsigned char                   std_key[22];
unsigned char                   multi_key[2];

unsigned char                   gKeyScan_bak[iMATRIX_COL_NUM];
unsigned char                   gKey_delay[21];

unsigned char                   device_type_bak;
unsigned int                    press_default_led_time_count;

unsigned char                   led_index;
unsigned char                   col_index;

/******************************************************************************
* 函数名称: void key_process(void)
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void key_process(void)
{
    unsigned char i;

    if(!bwin_mac_sataus)
    {                                           // mac系统，按键交换
        temp_bit = modifier_key_tmp;
        modifier_key_tmp &= 0x33;
        if(btemp_bit7)
            modifier_key_tmp |= 0x40;
        if(btemp_bit6)
            modifier_key_tmp |= 0x80;
        if(btemp_bit2)
            modifier_key_tmp |= 0x08;
        if(btemp_bit3)
            modifier_key_tmp |= 0x04;
    }

    if((!bkb_tx_busy&&(iUART_TX_IDLE==cmd_tx_index)) || bconn_type_usb)
    {
        for(i=0; i<6; i++)
        {
            if(key_data_tmp[i] != std_key[i])
            {
                memcpy(std_key, tmp_std_key, 6);
                std_key[6] = 0;

                bstd_data_send = 1;
                return;
            }
        }

        for(i=7; i<22; i++)
        {
            if(tmp_std_key[i] != std_key[i])
            {
                memcpy(std_key+7, tmp_std_key+7, 15);

                bstd_exdata_send = 1;
                return;
            }
        }

        if(multi_data_tmp_l != multi_key[0])
        {
		    if(!bmmk_data_send)
            {
			    multi_key[0] = multi_data_tmp_l;
                multi_key[1] = multi_data_tmp_h;
                bmmk_data_send = 1;
		    }
        }
    }
}

/******************************************************************************
* 函数名称: mode_swtich_init
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void mode_swtich_init(void)
{
    load_led_para();
    bdevice_switch = 1;
    // if((iCTRL_CMD_BT0 == device_type)
    //     ||(iCTRL_CMD_BT1 == device_type)
    //     ||(iCTRL_CMD_BT2 == device_type))
    if(iCTRL_CMD_BT0 == device_type)
        bdevice_bt_info = 1;

    cmd_tx_init();
    bsave_flash = 1;
    mode_swtich_time_count = 0;
    bdevice_conn = 0;
    bom6621d_conning = 0;
    bom6621d_conn_ok = 0;
	bmode_swtich_hint = 1;
	bled_hint_ing = 0;
    usb_status_reg &= 0xF8;
    bom6621d_disconn_sleep = 0;

    sleep_time = 0;
	uart_tick_count = 0;

	memset(std_key, 0x00, 22);

    bstd_data_send = 1;
    bstd_exdata_send = 1;

    multi_key[0] = 0;
    multi_key[1] = 0;
    bmmk_data_send = 1;
}

/******************************************************************************
* 函数名称: matrixkey_value
* 功能描述: 矩阵按键扫描
* 输入参数:
* 输出参数:
* 说    明: 为提高时间效率,赋值等操作不采用循环模式
******************************************************************************/
void matrixkey_value(void)
{
    unsigned char i;

    device_key = 0;
    special_key = 0;

    modifier_key_tmp = 0;
    multi_data_tmp_l = 0;
    multi_data_tmp_h = 0;

    bkey_press_status = 0;

    led_index = 0;
    for(col_index=0; col_index<iMATRIX_COL_NUM; col_index++)
    {
GIEH = 0;
        key_temp_flag_1 = (gKeyScan_bak[col_index] ^ matrix_status[col_index]);
        gKeyScan_bak[col_index] = matrix_status[col_index];
GIEH = 1;

        key_temp_flag = gKeyScan_bak[col_index];
// 0
        for(i=0; i<iMATRIX_ROW_NUM; i++)
        {
            if(bkey_temp0)
			{
                define_key_flag_n |= bdefine_key_press;
                bkey_press_status = 1;
                sleep_time = 0;
			}
		    else
                define_key_flag_n &= ~bdefine_key_press;

            if(0 == (define_key_flag_n&bkey_decode))
            {
                if(bkey_temp10)
                {                                   // 按键有变化
                    if(bkey_temp0)
                    {                               // 按下到松开,延时发送状态
                        define_key_flag_n = (bdefine_key_press|bkey_decode);
                        if(define_key_ctrl & bcom_key_break)
                        {                                           // 按键可打断
                            define_key_ctrl &= ~bcom_key_break;
                            bkey_status_change = 1;
                        }

                        if(bled_mode_single)
                        {
                            pwm_duty_array_0[led_index] = iPWM_MAX;
                            pwm_duty_array_1[led_index]++;
                            if(7<pwm_duty_array_1[led_index])
                                pwm_duty_array_1[led_index] = 1;
                        }
                        low_hint_time = 0;
                    }
                    goto define_key_process;
                }
                else
                {
		    	    if(led_index == com_key_index)
		    		    com_key_index = 0xFF;
                }
            }
            else
            {
                if(bkey_temp10)
                {                                   // 有变化
                    if(bkey_temp0)
                    {
                        if(define_key_ctrl & bcom_key_break)
                        {                                           // 按键可打断
                            define_key_ctrl &= ~bcom_key_break;
                            bkey_status_change = 1;
                        }

                        if(bled_mode_single)
                        {
                            pwm_duty_array_0[led_index] = iPWM_MAX;
                            pwm_duty_array_1[led_index]++;
                            if(7<pwm_duty_array_1[led_index])
                                pwm_duty_array_1[led_index] = 1;
                        }
                    }
                }
define_key_process:
                key_decode();
                if(bkey_decode_valid)
                {
                    if((define_key_flag&bkey_decode_end)
			    	    && (0==(define_key_flag&bdefine_key_press)))
                    {
                        define_key_flag = 0;
                    }
                    define_key_flag_n = define_key_flag;
                    if(define_key_flag&bdefine_key_com)
                    {
                        decode_data_l_n = decode_data_l;
                        decode_data_h_n = decode_data_h;
                    }
                }
                if(!bkey_temp0)
			        key_fn_status[led_index] = iNULL_MATRIX;
            }
            
            key_temp_flag>>=1;
			key_temp_flag_1>>=1;
            led_index++;     
        }
    }

    if(bkey_break_or_realse)
    {
        bkey_break_or_realse = 0;
        memset(key_data_tmp, 0x00, 22);
    }
    else
    {
        if(!bkey_press_status && (0 == (define_key_ctrl&bcom_decode_ing)))
        {
            memset(key_data_tmp, 0x00, 22);
        }
    }

// 按键去抖处理_END
    device_key_bak &= device_key;
    special_key_bak &= special_key;

    if(bfn_press != bfn_key_status)
    {
        bfn_key_status = bfn_press;
        if(!bfn_press&&bfn_save_flash)
        {
            bfn_save_flash = 0;
            bsave_6621d = 1;
            save_6621d_delay = 0;
        }
    }
}


/******************************************************************************
* 函数名称: matrixkey_scan
* 功能描述: 矩阵按键扫描
* 输入参数:
* 输出参数:
* 说    明: 为提高时间效率,赋值等操作不采用循环模式
******************************************************************************/
void matrixkey_scan(void)
{
    unsigned char i;

    uart_tick_count++;
    if(4 < power_on_time)
    {
	    uart_tick_count+=3;
	}
    if(250 <= uart_tick_count)
    {
        if(iCMD_IDLE == cmd_tx_index)
        {
            bbat_updata = 1;
            uart_tick_count = 0;
        }
    }

    matrixkey_value();
    key_process();
	if(iKEY_FN_R == matrix_status[iKEY_FN_C])
	{
	    if(iCLEAR_INFO_R == matrix_status[iCLEAR_INFO_C])
	    {
	        if(!bdefault_led_press)
	        {
	            bdefault_led_press = 1;
	            press_default_led_time_count = 0;
	        }
	        else
	        {
	            if(600 == press_default_led_time_count)
	            {
                    //if(iCMD_IDLE == cmd_tx_index)
				    {
                        clr_all_rgb();
                        //if(bcharge_ing)
                        {
							s_para = 0xA0|iWIN_MODE;
	                        led_default_load(); // 只在插USB线模式下才恢复灯效数据
                            memcpy(om6621d_flash_dat, s_para_tbl, 16);

                            bom6621d_flash_w = 1;
                            buart_flash_ok = 0;
                        }

                        for(i=0; i<2; i++)
                        {
                            set_rgb();
                            delayms(250);
                            clr_rgb();
                            delayms(250);
                        }
                        flash_clear(0);
                        flash_clear(1);
                        flash_clear(14);
                        flash_clear(15);

                        bcfg_reset = 1;
						bdevice_clear = 1;
                        bdevice_status_change = 1;
                        led_pre_mode = iMODE_LED_INVALID;

                        press_default_led_time_count++;
                    }
	            }
	            else if(600 > press_default_led_time_count)
	            {
	                press_default_led_time_count++;
	            }
	        }
	    }
	}
	else
	{
        bdefault_led_press = 0;
	}
    mode_swtich(100);
}
unsigned char rf_channel,b5v_check_in;
unsigned char channel;
void mode_swtich(unsigned char delay_en)
{
    static unsigned char delay = 0;
    
    if(PF4==0)
        bwin_mac_sataus = 0;
    else
        bwin_mac_sataus = 1;

    if(PA0)
        channel = iDEVICE_TYPE_24G;
    else if(PA1)
        channel = iDEVICE_TYPE_BT0;
    else if(PF7)
        channel = iDEVICE_TYPE_USB;
        
    if (channel != rf_channel)
    {
        if (++delay >= delay_en)
        {
            if (channel != iDEVICE_TYPE_USB) // 2.4G / BLE
            {
                rf_channel = channel;
                if(b5v_check_in)
                {
                    b5v_check_in = 0;
                    USBD_disable();
                }       

                if (iDEVICE_TYPE_24G == channel)
                {
                    sys_ctrl_reg &= 0xF0;
                    sys_ctrl_reg |= iDEVICE_TYPE_24G;
                    if(iCTRL_CMD_24G != device_type)
                    {
                        device_type = iCTRL_CMD_24G;
                        USBD_disable();
                        mode_swtich_init();
                        return;
                    }
                }
                else if (iDEVICE_TYPE_BT0 == channel)
                {
                    sys_ctrl_reg &= 0xF0;
                    // if(iDEVICE_TYPE_BT1 == bt_index)
                    // {
                    //     sys_ctrl_reg |= iDEVICE_TYPE_BT1;
                    //     if(iCTRL_CMD_BT1 != device_type)
                    //     {
                    //         device_type = iCTRL_CMD_BT1;
                    //         USBD_disable();
                    //         mode_swtich_init();
                    //         return;
                    //     }
                    // }
                    // else if(iDEVICE_TYPE_BT2 == bt_index)
                    // {
                    //     sys_ctrl_reg |= iDEVICE_TYPE_BT2;
                    //     if(iCTRL_CMD_BT2 != device_type)
                    //     {
                    //         device_type = iCTRL_CMD_BT2;
                    //         USBD_disable();
                    //         mode_swtich_init();
                    //         return;
                    //     }
                    // }
                    // else //if(iDEVICE_TYPE_BT0 == bt_index)
                    // {
                        sys_ctrl_reg |= iDEVICE_TYPE_BT0;
                        if(iCTRL_CMD_BT0 != device_type)
                        {
                            device_type = iCTRL_CMD_BT0;
                            USBD_disable();
                            mode_swtich_init();
                            return;
                        }
                    // }
                }
            }
            else // USB
            {
                if(!b5v_check_in)
                {
                    b5v_check_in = 1;
                    USBD_Init();
                    busb_boot = 0;
                    busb_suspend_en = 1;
                    return;
                }

                rf_channel = channel;

                if((iDEVICE_TYPE_USB != (sys_ctrl_reg&0x0F)))
                {
                    sys_ctrl_reg &= 0xF0;
                    sys_ctrl_reg |= iDEVICE_TYPE_USB;
                    if(iCTRL_CMD_IDLE != device_type)
                    {
                        device_type = iCTRL_CMD_IDLE;
                        USBCON |= BIT_USHC;
                        mode_swtich_init();
                        return;
                    }
                }
            }
        }        
    }
    else
    {
        delay = 0;
    }
}

/******************************************************************************
* 函数名称: scan_mode_swtich
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
unsigned char scan_mode_swtich(void)
{
    IODICR = 0x00;
    IODCHIE = 0;
    IOFICR = 0x00;
    IOFCHIE = 0;

    IOB |= 0xFF;
    IOC |= 0xFF;
    delayus(50);

    PWM_C2_LOW;
    delayus(100);
    matrix_status[2] = (~MATRX_R&0x7C);
    PWM_C2_HIGH;

    PWM_C3_LOW;
    delayus(100);
    matrix_status[3] = (~MATRX_R&0x7C);
    PWM_C3_HIGH;

    PWM_C4_LOW;
    delayus(100);
    matrix_status[4] = (~MATRX_R&0x7C);
    PWM_C4_HIGH;

    PWM_C6_LOW;
    delayus(100);
    matrix_status[6] = (~MATRX_R&0x7C);
    PWM_C6_HIGH;

    PWM_C10_LOW;
    delayus(100);
    matrix_status[10] = (~MATRX_R&0x7C);
    PWM_C10_HIGH;

    if(iKEY_FN_R != (matrix_status[10]&iKEY_FN_R))
        return 0;

    if(iKEY_BT0_R == (matrix_status[2]&iKEY_BT0_R))
    {
        sys_ctrl_reg &= 0xF0;
        sys_ctrl_reg |= iDEVICE_TYPE_BT0;
        if(iCTRL_CMD_BT0 != device_type)
        {
            device_type = iCTRL_CMD_BT0;
            USBD_disable();
            mode_swtich_init();
            return 1;
        }
    }
    else if(iKEY_BT1_R == matrix_status[3])
    {
        sys_ctrl_reg &= 0xF0;
        sys_ctrl_reg |= iDEVICE_TYPE_BT1;
        if(iCTRL_CMD_BT1 != device_type)
        {
            device_type = iCTRL_CMD_BT1;
            USBD_disable();
            mode_swtich_init();
            return 1;
        }
    }
    else if(iKEY_BT2_R == matrix_status[4])
    {
        sys_ctrl_reg &= 0xF0;
        sys_ctrl_reg |= iDEVICE_TYPE_BT2;
        if(iCTRL_CMD_BT2 != device_type)
        {
            device_type = iCTRL_CMD_BT2;
            USBD_disable();
            mode_swtich_init();
            return 1;
        }
    }
    else if(iKEY_24G_R == matrix_status[6])
    {
        sys_ctrl_reg &= 0xF0;
        sys_ctrl_reg |= iDEVICE_TYPE_24G;
        if(iCTRL_CMD_24G != device_type)
        {
            device_type = iCTRL_CMD_24G;
            USBD_disable();
            mode_swtich_init();
            return 1;
        }
    }
    return 0;
}

