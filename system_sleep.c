/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: System_Sleep.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include "defines.h"

//-----------------------------------------------------------------------------;
// 变量定义
//
unsigned char                   power_on_time;
unsigned int                    sleep_time;
unsigned int                    low_hint_time;

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

void off_rgb(void)
{
    pwm2_init();

    IOB = 0xFF;
    IOC = 0xFF;
    IOD = 0x00;
    IOE = 0x40;
}
void led_c_off(void)
{
    IOB = 0xFF;
    IOC = 0xFF;
    IOD = 0xFF;
    IOE = 0xFF;
}

/******************************************************************************
* 函数名称: in_sleep_init()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void in_sleep_init(void)
{
    GIEH = 0;
//----------------------------------------------
// 关背光灯,矩阵输出低
    off_rgb();

//----------------------------------------------
// 设置IO唤醒使能
    IOAICR = 0x7C;
    IOACHIE = 1;
    IOFICR = 0x84;
    IOFCHIE = 1;
    IOACHIF = 0;
    IOFCHIF = 0;

//----------------------------------------------
// 关闭串口
    //PUF |= 0x0C;
    TX0CR = 0x00;
    RX0CR = 0x00;
    RX0IE = 0;

//----------------------------------------------
// 关闭timer
	timer0_off();
}

/******************************************************************************
* 函数名称: system_sleep()
* 功能描述: 系统休眠处理
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void out_sleep_init(void)
{
    IOAICR = 0x00;
    IOACHIE = 0;
    IOFICR = 0x00;
    IOFCHIE = 0;

    off_rgb();
    timer0_init();

    bbat_updata = 0;
    blvd_status = 0;

    led_pre_mode = iMODE_LED_INVALID;
    sleep_time = 0;

    GIEH = 1;
}

/******************************************************************************
* 函数名称: system_sleep()
* 功能描述: 系统休眠处理
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void system_sleep(void)
{
    unsigned char i;

    if(4 < power_on_time)
        return;

    buart_ready = 1;
    if(bmode_swtich_hint)
        return;

    if(bconn_type_usb)
    {
        if(!busb_suspend_en)
            return;

        if(busb_boot)
        {
    	    busb_suspend_en = 0;
            return;
        }

	    timer0_off();

	    IOFICR &= ~0X03;
	    SwBusTimer = 0;
        in_sleep_init();

sleep_process_begin:
        if(!bwakeup_usb_enable)                 // USB不能唤醒PC.
        {
            led_c_off();

            IOAICR = 0x00;                      // usb休眠下，只允许FN + 1\2\3唤醒
            IOACHIE = 0;
            IOACHIF = 0;
            IOFICR = 0x03;
            IOFCHIE = 1;
            IOFCHIF = 0;

            GIEH = 1;

			INTF0 = 0;
			INTF1 = 0;
			INTF2 = 0;
            while(1)
            {
                if(busb_suspend_en)
                {
                    delayms(10);
                    if(0 != scan_mode_swtich())
                    {
				        goto usb_mode_change;
                    }
                }
	            if(UBRST || UBRSM || !busb_suspend_en)
                    break;
            }
        }
        else                                    // USB可唤醒PC.
        {

            gtemp_i = (IOA&0x7C);
            GIEH = 1;

            STPH = 1;
            STPL = 1;
            STOP = 1;
			nop;

            delayms(1);
            if(gtemp_i != (IOA&0x7C))
            {
                IOACHIF = 0;
                IOFCHIF = 0;

                if(0 != scan_mode_swtich())
                {
usb_mode_change:
                    uart_init();
                    IOFCHIF = 0;
                    delayms(1);
                    uart_invalid();
                    out_sleep_init();
                    delayms(10);
                    return;
                }

                IOF0 = 0;
                IOF1 = 1;
                OEF0 = 1;
                OEF1 = 1;
                UE = 0; 			              // 开始远程唤醒
                uart_init();                      // 协议规定时间应介于1ms-15ms之间
				delayms(1);
                uart_invalid();
				delayms(9);
                UE = 1;
                OEF0 = 0;
                OEF1 = 0;
            }
            busb_suspend_en = 0;
        }
        uart_init();
        GIEH = 1;
	    delayms(10);

        if(busb_suspend_en)
            goto sleep_process_begin;

	    USBSwState = 0;
        out_sleep_init();
        USBD_SwBusInit();
    }
    else
    {
        if(!bom6621d_conn_ok)
        {
            if(iDEVICE_TYPE_24G == (sys_ctrl_reg&0x0F))
            {
                if(iWORK_20S_TIME > sleep_time)
                    return;
            }
            else
            {
                if(bom6621d_conning)
                    return;

                if(iWORK_2MIN_TIME > sleep_time)
                    return;
            }
            //off_bt_led();
            in_sleep_init();
            bdevice_conn = 0;
            bom6621d_conning = 0;

            goto into_deep_sleep;
        }
        else
        {
            if(iCMD_IDLE != cmd_tx_index)
                return;

            if(iKB_WORK_5MIN_TIME > sleep_time)
                return;
        }

        //off_bt_led();
        in_sleep_init();

        sleep_time = 0;

into_sleep_1:
        T0CR =0x47;
        TC0CH = 0x00;
	    TC0CL = 0x00;
	    TC0IF = 0;
	    TC0EN = 1;
	    TC0IE = 1;
        sleep_time += iKB_WORK_5MIN_TIME;

        while(1)
        {
            TC0IF = 0;
            IOACHIF = 0;
            IOFCHIF = 0;

            STPH = 1;
            STPL = 0;
            STOP = 1;
			nop;

            if(TC0IF)
            {
                TC0IF = 0;
                sleep_time++;
                if((iKB_SLEEP_TIME <= sleep_time) || !bom6621d_conn_ok)
                    goto into_deep_sleep;
            }
            else
            {
                if(IOFCHIF)
                {
                    IOFCHIE = 0;
                    IOFCHIF = 0;
	                timer0_off();

                    uart_init();
                    delayms(1);
                    uart_invalid();
                    GIEH = 1;
                    bwakeup_en = 0;
                    for(i=0; i<50; i++)
                    {
                        delayms(1);
                        uart_rx_decode();
                        if(bwakeup_en)
                            goto sleep_1_wakeup;
                    }
                    GIEH = 0;
                    IOFCHIE = 1;
                    goto into_sleep_1;
                }
                else
                {
                    uart_init();
                    delayms(1);
                    uart_invalid();
                    IOACHIF = 0;
                    break;
                }
            }
        }
sleep_1_wakeup:
	    out_sleep_init();
        return;

into_deep_sleep:
	    timer0_off();
        IOACHIF = 0;
        IOFCHIF = 0;
        off_bt_module();

        STPH = 1;
        STPL = 1;
        STOP = 1;
        nop;

        IOACHIF = 0;

        uart_init();
        IOFCHIF = 0;
        delayms(1);
        uart_invalid();

	    out_sleep_init();
        delayms(10);

        bom6621d_conn_ok = 0;
        bdevice_conn = 0;
		bom6621d_disconn_sleep = 0;

        device_type = device_type_bak;
        bdevice_switch = 1;
        cmd_tx_init();
    }
}
