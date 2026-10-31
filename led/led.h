/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_H_
#define _LED_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 配置常量定义区
//
#define iLED_COL_NUM            15
#define iLED_ROW_NUM        	5
#define iLED_NUM_MAX         	(15*iLED_ROW_NUM)
#define iLED_MAX         	    (15*iLED_ROW_NUM)

//----------------------------------------------
// led闪烁常量定义
//
#define iBAT_POWER_OFF          0
#define iBAT_POWER_LOW          20

#define iMODE_HINT_TIME         (2000/4)       // 2s
#define iCONN_HOLD_TIME         (2*60000/4)    // 2min
#define iCONN_OK_TIME           (3000/4)       // 3s

//-----------------------------------------------------------------------------;
// 配置区
//
// #define LED_CAPS_PIN                PE6
#define CHARGE_OK_PIN               PF6
#define USB5V_CHEKC_PIN             PF7

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//
//-----------------------------------------------------------------------------;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部引用区      
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
// 
extern USBD_U16                  uhint_led_status;
//{
    #define hint_led_status     uhint_led_status.u16

    #define blvd_breath_delay   uhint_led_status.BIT.b10
    #define blvd_enable         uhint_led_status.BIT.b9
    #define blvd_breath_status  uhint_led_status.BIT.b8

    #define bbat_hint_en        uhint_led_status.BIT.b7
    #define bwin_mac_hint       uhint_led_status.BIT.b6
    #define blvd_status         uhint_led_status.BIT.b5
    #define bcharge_ing         uhint_led_status.BIT.b4
    #define bcharge_ok          uhint_led_status.BIT.b3

    #define bwin_lock_sctaus    uhint_led_status.BIT.b2
    #define bwin_lock_hint_en   uhint_led_status.BIT.b1
//}

extern unsigned char            bat_r_value;
extern unsigned char            bat_g_value;
extern unsigned char            bat_b_value;
extern unsigned char            charge_time_count;
extern unsigned int             charge_ok_time_count;

//-----------------------------------------------------------------------------;
// 函数引用
//
extern void power_5v_on(void);
extern void power_5v_off(void);

extern void hint_led_on(void);
extern void hint_led_off(void);

extern void led_hint_process(void);
//
//-----------------------------------------------------------------------------;
#endif
