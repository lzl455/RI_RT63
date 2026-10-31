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
USBD_U8                         uuart_ctrl;
USBD_U16                        utx_cmd_flag;
USBD_U8                         uom6621d_status;

unsigned char                   device_type;
unsigned char                   device_type_bak;

unsigned char                   uart_rx_delay;
unsigned char                   rx_r_index;

unsigned char                   uart_rx_buff[iUART_RXBUF_SIZE];
unsigned char                   uart_tx_buff[iUART_TXBUF_SIZE];

unsigned char                   bat_power_value;
unsigned char                   bat_value_ble;

unsigned char                   bat_power_adc_value;
unsigned char                   data_tx_delay_count;
unsigned char                   conn_time_count;
#define om6621d_flash_delay     conn_time_count
unsigned char                   charge_time_count_l;

unsigned char                   device_conn_index;
//unsigned char                   wheel_data_6621d;

unsigned char                   om6621d_flash_dat[20];
unsigned char                   bat_init_value,bat_init_value_bak;
/*
unsigned char                   om6621d_led_pin;
unsigned char                   om6621d_led_lev;
unsigned char                   om6621d_led_off_time;
unsigned char                   om6621d_led_on_time;
unsigned char                   om6621d_led_times;
*/
//-----------------------------------------------------------------------------;
// 表格定义区
//
unsigned char const bt_device_info_tbl_bt0[] =
{
	'R','i','i',' ','K','6','8',0,
	0,0,0,0,0,0,0,0,
	0,0,
};

unsigned char const bat_value_tbl[39] = 
{
     0, 0, 0, 0, 5, 5, 5, 10, 10,10,
    20,20,30,30,30,40,40,40,40,50,
    50,50,60,60,60,70,70,70,80,80,
    80,90,90,90,100,100,100,100,100,
};

#define iBAT_VALUE_ERR          (200/3)           // 0%    0 
#define iBAT_VALUE_0            (300/3)           // 0%    0 
#define iBAT_VALUE_5            (330/3)           // 5%    1 
#define iBAT_VALUE_10           (340/3)           // 10%   2 
#define iBAT_VALUE_20           (345/3)           // 20%   3 
#define iBAT_VALUE_30           (353/3)           // 30%   4 
#define iBAT_VALUE_40           (357/3)           // 40%   5 
#define iBAT_VALUE_50           (360/3)           // 50%   6 
#define iBAT_VALUE_60           (365/3)           // 60%   7 
#define iBAT_VALUE_70           (372/3)           // 70%   8 
#define iBAT_VALUE_80           (381/3)           // 80%   9 
#define iBAT_VALUE_90           (390/3)           // 90%   10
#define iBAT_VALUE_100          (402/3)           // 100%  134

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;

/******************************************************************************
* 函数名称: uart_init
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void uart_init(void)
{
    TX0CR = 0x80;       //使能串口发送功能、异步模式、8位数据、波特率预分频比为4、不发送第九位数据
    RX0CR = 0xC0;       //使能串口接收功能、上升沿发送数据、8位数据、不接收第9位数据

    BRGD0H=0x00;
    BRGD0L=51;          // 115200bps

    TX0IF = 0;          //清中断标志
    RX0IF = 0;          //清中断标志
    TX0IE = 0;          //屏蔽串行通讯发送中断
    RX0IE = 1;          //使能串行通讯接收中断

    PUF &= ~0x0C;
}

unsigned char                   uart_tx_index;
unsigned char                   uart_retx_count;
unsigned char                   uart_tx_delay;
unsigned char                   uart_tick_count;
unsigned char                   uart_cmd_delay;
unsigned char                   uart_length;

/******************************************************************************
* 函数名称: uart_rsp
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void uart_rsp(void)
{
    mUART_BYTE_TX(iUART_CMD_RSP_0);
    nop;
    mUART_BYTE_TX(iUART_CMD_RSP_1);
    nop;
    mUART_BYTE_TX(iUART_CMD_RSP_2);
    uart_cmd_delay = 0;
}

#define iUART_TX_BEGIN          0x00
#define iUART_TX_ING            0x01
#define iUART_TX_OK             0xFE
#define iUART_TX_ERR            0xFF
#define iUART_RETX_COUNT_MIN    3
#define iUART_RETX_COUNT_MAX    10

void uart_tx_init(void)
{
    buart_rsp_ok = 0;
    uart_tx_delay = 0;
    uart_tx_index = iUART_TX_IDLE;
    uart_retx_count = 0;
}

/******************************************************************************
* 函数名称: uart_tx
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明: 内部包含3次重发
******************************************************************************/
void uart_tx(unsigned char lenght)
{
    unsigned char i,j;

    if(iUART_TX_IDLE == uart_tx_index)
    {
        if(20<lenght)
            lenght = 20;

        i = 0;
        for(j=0; j<lenght; j++)
        {
            mUART_BYTE_TX(uart_tx_buff[j])
            i += uart_tx_buff[j];
        }
        mUART_BYTE_TX(i);

        uart_tx_delay = 0;
        uart_tx_index = iUART_TX_ING;
    }
    else if(iUART_TX_ING == uart_tx_index)
    {
        if(buart_rsp_ok)
        {
            uart_tx_index = iUART_TX_OK;
            bretey_count = 0;
        }
        else
        {
            if(100 < uart_tx_delay)
            {
                uart_tx_delay = 0;
                uart_tx_index = iUART_TX_IDLE;

                uart_invalid();
                delayms(2);

                uart_retx_count++;
                if(bretey_count)
                {
                    if(iUART_RETX_COUNT_MIN <= uart_retx_count)
                    {
                        uart_tx_index = iUART_TX_ERR;
                        bretey_count = 0;
                    }
                }
                else
                {
                    if(iUART_RETX_COUNT_MAX <= uart_retx_count)
                        uart_tx_index = iUART_TX_ERR;
                }
            }
        }
    }
}

unsigned char                   cmd_tx_index;
#define cmd_tx_delay            uart_tx_delay

void cmd_tx_init(void)
{
    cmd_tx_index = iCMD_TX_BEGIN;
}

/******************************************************************************
* 函数名称: hint_led_on
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void uart_invalid(void)
{    
    mUART_BYTE_TX(iUART_CMD_CTRL);
    mUART_BYTE_TX(iCMD_INVALID);
    mUART_BYTE_TX(iUART_CMD_CTRL);
}

void om6621d_bt_info_check(void)
{    
    mUART_BYTE_TX(iUART_CMD_CTRL);
    mUART_BYTE_TX(iCTRL_CMD_BAT_INFO);
    mUART_BYTE_TX(0xF9);
}

/******************************************************************************
* 函数名称: om6621d_ctrl_cmd
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void om6621d_ctrl_cmd(unsigned char type, unsigned char cmd)
{    
    if(iCMD_TX_BEGIN == cmd_tx_index)
    {
        switch(type)
        {
            case iCMD_STD:
                if(iCTRL_CMD_BAT_INFO == cmd)
                {
                    bretey_count = 1;
                    bdevice_bat_info = 0;
                }
                else if(iCTRL_CMD_BAT_INFO == cmd)
                {
                    om6621d_flash_delay = 0;
                }
                uart_tx_buff[0] = iUART_CMD_CTRL;
                uart_tx_buff[1] = cmd;

                uart_length = iUART_LENGHT_CTRL;
                break;
            case iCMD_BT_INFO:
                uart_tx_buff[0] = iUART_CMD_BT_INFO;
                uart_tx_buff[1] = iUART_LENGHT_BT_INFO;
                for(gtemp_i=0; gtemp_i<18; gtemp_i++)
                    uart_tx_buff[gtemp_i+2] = bt_device_info_tbl_bt0[gtemp_i];
                if(iCTRL_CMD_BT1 == device_type)
                    uart_tx_buff[7+2] = '2';
                else if(iCTRL_CMD_BT2 == device_type)
                    uart_tx_buff[7+2] = '3';

                uart_length = iUART_LENGHT_BT_INFO+2;
                break;
            case iCMD_DEVICE_SWITCH:
                uart_tx_buff[0] = iUART_CMD_CTRL;
        
                if(iCTRL_CMD_IDLE == device_type)
                {
                    uart_tx_buff[1] = iCTRL_CMD_IDLE;
                    if(bconn_type_usb && busb_suspend_en && !bwakeup_usb_enable)
                        uart_tx_buff[1] = iCTRL_CMD_OFF;
                }
                else if(iCTRL_CMD_BT1 == device_type)
                    uart_tx_buff[1] = iCTRL_CMD_BT1;
                else if(iCTRL_CMD_BT2 == device_type)
                    uart_tx_buff[1] = iCTRL_CMD_BT2;
                else if(iCTRL_CMD_24G == device_type)
                    uart_tx_buff[1] = iCTRL_CMD_24G;
                else //if(iCTRL_CMD_BT0 == device_type)
                    uart_tx_buff[1] = iCTRL_CMD_BT0;

                uart_length = iUART_LENGHT_CTRL;
                break;
            case iCMD_FLASH_W:
                uart_tx_buff[0] = iUART_CMD_FLASH_W;
                memcpy(uart_tx_buff+1, om6621d_flash_dat, 17);

                uart_length = iUART_LENGHT_FLASH_W;
                break;

            case iCMD_BAT_UPDATE:
                uart_tx_buff[0] = iUART_CMD_BAT_VALUE;
                if(100<bat_value_ble)
                    uart_tx_buff[1] = 100;
                else
                    uart_tx_buff[1] = bat_value_ble;
                bretey_count = 1;

                uart_length = iUART_LENGHT_CTRL;
                break;
                
            case iCMD_KB_DATA:
                bkb_tx_busy = 1;
                uart_length = cmd;
                break;
        }

        uart_tx_init();
        cmd_tx_index = iCMD_TX_ING;
        uart_tx(uart_length);
    }
    else if(iCMD_TX_ING == cmd_tx_index)
    {
        uart_tx(uart_length);
        if(iUART_TX_OK == uart_tx_index)
        {
            cmd_tx_delay = 0;
            cmd_tx_index = iCMD_RSP_OK;
            bkb_tx_busy = 0;
        }
        else if(iUART_TX_ERR == uart_tx_index)
        {
            cmd_tx_index = iCMD_RSP_ERR;
            bkb_tx_busy = 0;
        }
    }
}

/******************************************************************************
* 函数名称: hint_led_on
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void om6621d_device_conn(void)
{
    if(iCMD_TX_BEGIN == cmd_tx_index)
    {
        bom6621d_conning = 0;
        bom6621d_conn_ok = 0;
        device_conn_index = 0;
        conn_time_count = 0;

        uart_tx_buff[0] = iUART_CMD_CTRL;
        uart_tx_buff[1] = iCTRL_CMD_CONN;
        uart_tx_init();
        cmd_tx_index = iCMD_TX_ING;
        uart_tx(iUART_LENGHT_CTRL);
    }
    else if(iCMD_TX_ING == cmd_tx_index)
    {
        uart_tx(iUART_LENGHT_CTRL);
        if(iUART_TX_OK == uart_tx_index)
        {
            cmd_tx_delay = 0;
            cmd_tx_index = iCMD_RX_ING;
        }
        else if(iUART_TX_ERR == uart_tx_index)
        {
            cmd_tx_index = iCMD_RSP_ERR;
        }
    }
    else if(iCMD_RX_ING == cmd_tx_index)
    {
        if(bom6621d_conn_ok)
        {
            cmd_tx_index = iCMD_RSP_OK;
        }
        else if(!bom6621d_conning)
        {
            if(250 <= cmd_tx_delay)
                cmd_tx_index = iCMD_RSP_ERR;
        }
    }
}

/******************************************************************************
* 函数名称: uart_process
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void uart_process(void)
{
    unsigned char i;

    if(2 > uart_cmd_delay)
        return;
    if(!buart_ready)
        return;

    if(bdevice_bt_info)
    {                                           // 发射蓝牙信息
        om6621d_ctrl_cmd(iCMD_BT_INFO, iUART_CMD_NULL);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bdevice_bt_info = 0;
            uart_cmd_delay = 0;
        }
        return;
    }
    else if(bdevice_switch)
    {
        om6621d_ctrl_cmd(iCMD_DEVICE_SWITCH, iUART_CMD_NULL);
        if((iCMD_RSP_ERR == cmd_tx_index) || (iCMD_RSP_OK == cmd_tx_index))
        {
            if(iCMD_RSP_OK == cmd_tx_index)
            {
                bdevice_clear = 0;
                bdevice_conn = 0;
                usb_data_flag = 0;
                device_type_bak = device_type;
            }
            uart_cmd_delay = 0;
            cmd_tx_init();

            uart_tick_count = 0;
            bkb_tx_busy = 0;
            bom6621d_sync_ing = 1;
            device_conn_index = 0;
            bdevice_switch = 0;
            if(!bconn_type_usb)
                usb_status_reg &= 0x78;         // 清除LED状态
        }
        data_tx_delay_count = 0;
        return;
    }
    else if(bom6621d_flash_w)
    {
        om6621d_ctrl_cmd(iCMD_FLASH_W, iUART_CMD_NULL);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            bom6621d_flash_w = 0;
            bom6621d_flash_r = 1;
            uart_cmd_delay = 0;
            cmd_tx_init();
        }
        return;
    }
    else if(bom6621d_flash_r)
    {
        om6621d_ctrl_cmd(iCMD_STD, iCTRL_CMD_FLASH_R);
        if(iCMD_RSP_OK == cmd_tx_index)
        {
            bom6621d_flash_r = 0;
            uart_cmd_delay = 0;
            cmd_tx_init();
        }
        else if(iCMD_RSP_ERR == cmd_tx_index)
        {
            led_default_load();
            load_led_para();
            buart_flash_ok = 1;

            bom6621d_flash_r = 0;
            uart_cmd_delay = 0;
            cmd_tx_init();
        }
        else
        {
            if(50 < om6621d_flash_delay)
            {
                bom6621d_flash_r = 0;
                cmd_tx_init();
            }
        }

        return;
    }

    if(bdevice_clear)
    {                                           // 无线对码
        om6621d_ctrl_cmd(iCMD_STD, iCTRL_CMD_CLEAR);
        if(iCMD_RSP_OK == cmd_tx_index)
        {
            cmd_tx_init();
            //bdevice_clear = 0;
            USBD_disable();
            clr_all_rgb();

            for(i=0; i<2; i++)
            {
                set_rgb();
                delayms(250);
                clr_rgb();
                delayms(250);
            }
            TC0EN = 0;
            TC0IE = 0;
            off_bt_module();                    // 关闭蓝牙模组，不可唤醒

            //flash_clear();
            delayms(10);
            Reset();
        }
        return;
    }

    if(bconn_type_usb)
    {
        if(bbat_updata)
        {
            om6621d_ctrl_cmd(iCMD_STD, iCTRL_CMD_BAT_INFO);
            if(iCMD_TX_ING != cmd_tx_index)
            {
                cmd_tx_init();
                bbat_updata = 0;
            }
        }
        return;
    }

    if(bdevice_conn)
    {                                           // 无线对码
        om6621d_device_conn();
        if(iCMD_RSP_OK == cmd_tx_index)
        {
            cmd_tx_init();
            bdevice_conn = 0;
        }
        else if(iCMD_RX_ING == cmd_tx_index)
        {
            if(250 < conn_time_count)
            {
                conn_time_count=0;
                om6621d_bt_info_check();
            }
        }
        else if(iCMD_RSP_ERR == cmd_tx_index)
        {
            bom6621d_conning = 0;
            bdevice_conn = 0;

            led_pre_mode = iMODE_LED_INVALID;
        }
        return;
    }

    if(250 > data_tx_delay_count)
    {
        uart_tick_count = 0;
        if(bom6621d_sync_ing)
            return;
    }

    if(bfn_data_send)
    {
        bfn_data_send = 0;
/*        uart_tx_buff[0] = iUART_CMD_FN;
        if(bmmk_fn_press)
            uart_tx_buff[1] = 0x10;
        else
            uart_tx_buff[1] = 0x00;
        om6621d_mk_data_tx(iUART_LENGHT_FN);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bfn_data_send = 0;
        }*/
    }
    else if(bstd_exdata_send)
    {
        uart_tx_buff[0] = iUART_CMD_EXK;
        memcpy(uart_tx_buff+1, std_key+7, 15);
        om6621d_ctrl_cmd(iCMD_KB_DATA, iUART_LENGHT_EX);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bstd_exdata_send = 0;
            if(iCTRL_CMD_24G == device_type)
            {                                   // 解决2.4G模式下按键自动松开的问题
                memset(std_key, 0x00, 5);
            }
        }
    }
    else if(bstd_data_send)
    {
        uart_tx_buff[0] = iUART_CMD_STDK;
        uart_tx_buff[1] = std_key[0];
        uart_tx_buff[2] = 0x00;
        memcpy(uart_tx_buff+3, std_key+1, 6);
        om6621d_ctrl_cmd(iCMD_KB_DATA, iUART_LENGHT_STDK);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bstd_data_send = 0;
        }
    }
    else if(bmmk_data_send)
    {
        uart_tx_buff[0] = iUART_CMD_MMK;
        uart_tx_buff[1] = multi_key[0];
        uart_tx_buff[2] = multi_key[1];
        om6621d_ctrl_cmd(iCMD_KB_DATA, iUART_LENGHT_MMK);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bmmk_data_send = 0;
            if(iCTRL_CMD_24G == device_type)
            {                                   // 解决2.4G模式下按键自动松开的问题
                memset(std_key, 0x00, 5);
            }
        }
    }
    else if(bbat_updata)
    {
        om6621d_ctrl_cmd(iCMD_STD, iCTRL_CMD_BAT_INFO);
        if(iCMD_TX_ING != cmd_tx_index)
        {
            cmd_tx_init();
            bbat_updata = 0;
        }
    }
    else if(bbat_info_updata)
    {
        if(iCTRL_CMD_24G != device_type_bak)
        {
            om6621d_ctrl_cmd(iCMD_BAT_UPDATE, iUART_CMD_NULL);
            if(iCMD_TX_ING != cmd_tx_index)
            {
                cmd_tx_init();
                bbat_info_updata = 0;
            }
        }
        else
        {
            bbat_info_updata = 0;
        }
    }
    else
    {
        cmd_tx_init();
    }
}

/******************************************************************************
* 函数名称: uart_rx_decode
* 功能描述:
* 输入参数:
* 输出参数:
* 说    明:
******************************************************************************/
void uart_rx_decode(void)
{
    unsigned char i, j;

    if(!buart_rx_ok)
        return;
    buart_rx_ok = 0;

    if(iUART_S_M != (uart_rx_buff[0]&0xF0))
        return;

    if(iUART_CMD_FLASH_DAT == uart_rx_buff[0])
    {
        j = 0;
        for(i=0; i<17; i++)
        {
            j += uart_rx_buff[i];
        }

        if(j == uart_rx_buff[17])
        {
            uart_rsp();
            buart_flash_ok = 1;
            memcpy(s_para_tbl, uart_rx_buff+1, 16);

            load_led_para();
            pwm2_init();
        }
        return;
    }

    if(iUART_CMD_BAT_INFO == uart_rx_buff[0])
    {                                           // 电池电量
        if(uart_rx_buff[4] != ((uart_rx_buff[0]+uart_rx_buff[1]+uart_rx_buff[2]+uart_rx_buff[3])&0xFF))
            return;

        bdevice_bat_info = 1;
        uart_rsp();
        buart_ready = 1;
        bat_init_value = 1;

//----------------------------------------------
// 模组状态
        bwakeup_en = 1;

        bom6621d_conn_ok = 0;
        //bcharge_ing = 0;
        //bcharge_ok = 0;
        //bwin_mac_sataus = 0;
        if(uart_rx_buff[2]&(1<<3))
        {
            bom6621d_conn_ok = 1;
            bom6621d_sync_ing = 0;
        }
        //if(uart_rx_buff[2]&(1<<4))
            //bcharge_ing = 1;
        //if(uart_rx_buff[2]&(1<<5))
            //bcharge_ok = 1;
        //if(uart_rx_buff[2]&(1<<6))
            //bwin_mac_sataus = 1;
//----------------------------------------------
// 通道状态
        if(!bconn_type_usb)
        {
            if((sys_ctrl_reg&0x07) != ((uart_rx_buff[3]&0x07)-1))
            {
                bdevice_switch = 1;
                cmd_tx_init();
            }
        }

        if(!bconn_type_usb && bom6621d_conn_ok)
        {
            usb_status_reg &= 0xF8;
            usb_status_reg |= (uart_rx_buff[2]&0x07);
        }

//----------------------------------------------
// 电量信息

//uart_rx_buff[1] = iBAT_VALUE_0;
        bbat_check_err = 0;
        if(bat_init_value!=bat_init_value_bak)
        {
            bat_power_adc_value = uart_rx_buff[1];
            bat_init_value_bak = bat_init_value;
            bbat_info_updata = 1;
        }
        if(iBAT_VALUE_100 < uart_rx_buff[1])
        {
            uart_rx_buff[1] = 36;
        }
        else if(iBAT_VALUE_0 > uart_rx_buff[1])
        {
            if(iBAT_VALUE_ERR < uart_rx_buff[1])
                uart_rx_buff[1] = 0;
            else
            {
                bbat_check_err = 1;
                uart_rx_buff[1] = 15;
            }
        }
        else
        {
            uart_rx_buff[1] -= iBAT_VALUE_0;
        }

        if(uart_rx_buff[1] < bat_power_adc_value)
           i = (bat_power_adc_value - uart_rx_buff[1]);
        else
           i = (uart_rx_buff[1] - bat_power_adc_value);
        bat_power_adc_value = uart_rx_buff[1];

        if(bbat_power_up || ((5<i) && (10<charge_time_count)))
        {
            bbat_power_up = 0;
            bat_power_value = uart_rx_buff[1];
            return;
        }
        i = uart_rx_buff[1];
        if(bat_power_value != i)
        {
            if(0xFF != charge_time_count)
            {
                if(100>charge_time_count)
                {
                    if(bcharge_ing)
                        j = 1;
                    else
                        j = 2;
                    if(j<charge_time_count_l)
                    {
                        charge_time_count_l = 0;
                        charge_time_count++;
                    }
                    charge_time_count_l++;
                    return;
                }
                charge_time_count=0;
            }

            if(bat_power_value > i)
                bat_power_value--;
            else
                bat_power_value++;
            if(bat_power_value == i)
                charge_time_count=0xFF;
        }

        i = bat_value_tbl[bat_power_value];
        if(bat_value_ble != i)
        {
            if(bcharge_ing)
            {
                if(4 < power_on_time)
                    bat_value_ble = i;
                else if(bat_value_ble<i)
                    bat_value_ble = i;
            }
            else
            {
                if(bat_value_ble>i)
                    bat_value_ble = i;
            }
            //bat_value_ble = i;
            bbat_info_updata = 1;
        }
        return;
    }

    if(uart_rx_buff[2] != ((uart_rx_buff[0]+uart_rx_buff[1])&0xFF))
        return;

    if(iUART_CMD_WHEEL == uart_rx_buff[0])
    {                                           // 滚轮数据
        //bwakeup_en = 1;
        //wheel_data_6621d += uart_rx_buff[1];
    }
    else if(iUART_CMD_BT_RSP == uart_rx_buff[0])
    {                                           // 控制信息
        if(iRSP_CMD_OUT_CONN == uart_rx_buff[1])
        {
            bom6621d_conning = 0;
            bdevice_conn = 0;

            rf_delay_time_count = 0;
            sleep_time = (iWORK_2MIN_TIME+1);

            led_pre_mode = iMODE_LED_INVALID;
        }
        else if(iRSP_CMD_INTO_CONN == uart_rx_buff[1])
        {
            if(!bdevice_conn)
            {
                cmd_tx_index = iCMD_RX_ING;
                bdevice_conn = 1;
                bom6621d_conn_ok = 0;
                device_conn_index = 0;
            }
            bom6621d_conning = 1;
        }
        else if(iRSP_CMD_CONN_OK == uart_rx_buff[1])
        {
            bom6621d_conn_ok = 1;
            b24g_bt_conn_ok = 0;
            bom6621d_sync_ing = 0;
            bom6621d_disconn_sleep = 0;
        }
        else if(iRSP_CMD_SWITCH_OK == uart_rx_buff[1])
        {
            bom6621d_switch_ok = 1;
        }
        else if(iRSP_CMD_INVAILD == uart_rx_buff[1])
        {
            bom6621d_standby = 1;
        }
        uart_rsp();
    }
    else if(iRSP_CMD_DIS_CONN == uart_rx_buff[0])
    {
        bom6621d_conn_ok = 0;
        if(iCTRL_CMD_IDLE==device_type)
            bom6621d_switch_ok = 1;

        if(!bom6621d_conning)
        {
            bom6621d_sync_ing = 1;
            device_conn_index = 0;
        }

        bom6621d_disconn_sleep = 0;
        if(iDIS_CONN_SELF != uart_rx_buff[1])
            bom6621d_disconn_sleep = 1;

        uart_rsp();
    }
    else if(iUART_CMD_LED_OFF == uart_rx_buff[0])
    {
        bom6621d_led_off = 1;
        uart_rsp();
    }
}

/******************************************************************************
* 函数名称: off_bt_module()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void off_bt_module(void)
{
    unsigned char i;

    IOACHIE = 0;
    IOFCHIE = 0;
    uart_init();
    rx_r_index = 0;
    uart_invalid();
    GIEH = 1;
    delayms(10);
    device_type = iCTRL_CMD_IDLE;
    bom6621d_switch_ok = 0;
    cmd_tx_init();
    for(i=0; i<200; i++)
    {
        if(0 == (uart_tx_delay&0x03))
        {
            if(0xFF != uart_cmd_delay)
                uart_cmd_delay++;
        }

        om6621d_ctrl_cmd(iCMD_DEVICE_SWITCH, iUART_CMD_NULL);
        if(iCMD_RSP_ERR == cmd_tx_index)
            i += 10;
        else if(iCMD_RSP_OK == cmd_tx_index)
        {
            if(bom6621d_switch_ok)
                i += 10;
        }

        uart_tx_delay++;
        uart_rx_delay++;
        if(3 < uart_rx_delay)
            rx_r_index = 0;
        delayms(1);
        uart_rx_decode();
    }
    cmd_tx_init();
    if(!bconn_type_usb)
        usb_status_reg &= 0x78;
    GIEH = 0;

    PUF |= 0x0C;
    TX0CR = 0x00;
    RX0CR = 0x00;
    RX0IE = 0;

    TC0IF = 0;
    IOACHIF = 0;
    IOFCHIF = 0;
    IOACHIE = 1;
    IOFCHIE = 1;
}

/******************************************************************************
* 函数名称: off_bt_led()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
/*void off_bt_led(void)
{
    unsigned char i;

    IOACHIE = 0;
    IOFCHIE = 0;
    uart_init();

    bom6621d_led_off = 0;
    cmd_tx_init();
    GIEH = 1;
    for(i=0; i<250; i++)
    {
        if(0 == (uart_tx_delay&0x03))
        {
            if(0xFF != uart_cmd_delay)
                uart_cmd_delay++;
        }

        om6621d_led_ctrl();
        if(iCMD_RSP_OK == cmd_tx_index)
        {
            if(bom6621d_led_off)
            {
                bom6621d_led_off = 0;
                i = 150;
            }
        }

        uart_tx_delay++;
        delayms(1);
        uart_rx_decode();
    }
    cmd_tx_init();
    GIEH = 0;

    TX0CR = 0x00;
    RX0CR = 0x00;
    RX0IE = 0;

    TC0IF = 0;
    IOACHIF = 0;
    IOFCHIF = 0;
    IOACHIE = 1;
    IOFCHIE = 1;
}
*/
/******************************************************************************
* 函数名称: get_bat_value()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void get_bat_value(void)
{
    unsigned char i;

    GIEH = 1;
    cmd_tx_init();
    for(i=0; i<250; i++)
    {
        if(0 == (uart_tx_delay&0x03))
        {
            if(0xFF != uart_cmd_delay)
                uart_cmd_delay++;
        }

        om6621d_ctrl_cmd(iCMD_STD, iCTRL_CMD_BAT_INFO);

        uart_tx_delay++;
        delayms(1);
        uart_rx_decode();
        if(bdevice_bat_info)
        {
            bdevice_bat_info = 0;
            break;
        }
    }
    cmd_tx_init();
    GIEH = 0;
}

/******************************************************************************
* 函数名称: get_bat_value()
* 功能描述:
* 输入参数: 无
* 输出参数: 无
* 说    明:
******************************************************************************/
void fcc_cmd_tx(unsigned char cmd)
{
    unsigned char i;

    cmd_tx_init();
    for(i=0; i<250; i++)
    {
        if(0 == (uart_tx_delay&0x03))
        {
            if(0xFF != uart_cmd_delay)
                uart_cmd_delay++;
        }

        if(iCMD_TX_BEGIN == cmd_tx_index)
        {
            bdevice_bat_info = 0;
            uart_tx_buff[0] = iUART_CMD_CTRL;
            uart_tx_buff[1] = cmd;
            uart_tx_init();
            bretey_count = 1;
            cmd_tx_index = iCMD_TX_ING;
        }
        else if(iCMD_TX_ING == cmd_tx_index)
        {
            uart_tx(iUART_LENGHT_CTRL);
            if(iUART_TX_OK == uart_tx_index)
            {
                cmd_tx_index = iCMD_RSP_OK;
                return;
            }
            else if(iUART_TX_ERR == uart_tx_index)
            {
                cmd_tx_index = iCMD_RSP_ERR;
                return;
            }
        }

        uart_tx_delay++;
        delayms(1);
    }
}