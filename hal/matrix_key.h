/*******************************************************************************
* Copyright (c) 2013, SHENZHEN Co.,LTD.
* All rights reserved.
*
* 文件名称: matrix_key.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef MATRIX_KEY_H1_
#define MATRIX_KEY_H1_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
//配置常量定义区
//
#define iMATRIX_COL_NUM         15
#define iMATRIX_ROW_NUM         5
#define iMATRIX_NUM_MAX         iMATRIX_COL_NUM*iMATRIX_ROW_NUM

#define iKEY_INDEX_BT0          (5*2 + 3)
#define iKEY_INDEX_BT1          (5*3 + 1)
#define iKEY_INDEX_BT2          (5*4 + 1)
#define iKEY_INDEX_USB          (5*5 + 1)
#define iKEY_INDEX_24G          (5*1 + 3)

#define iKEY_INDEX_FN           (5*10 + 0)
#define iKEY_INDEX_BAT          (5*6 + 1)

#define iKEY_FN_C               10
#define iKEY_FN_R               0x04
#define iKEY_BT0_R              0x08
#define iKEY_BT1_R              0x08
#define iKEY_BT2_R              0x08
#define iKEY_24G_R              0x08

#define iCLEAR_INFO_C           0               // escape键
#define iCLEAR_INFO_R           0x40

#define iKEY_INDEX_W            (5*2 + 3)
#define iKEY_INDEX_A            (5*1 + 2)
#define iKEY_INDEX_S            (5*2 + 2)
#define iKEY_INDEX_D            (5*3 + 2)

#define iKEY_INDEX_UP           (5*11 + 1)
#define iKEY_INDEX_DOWN         (5*11 + 0)
#define iKEY_INDEX_LEFT         (5*10 + 0)
#define iKEY_INDEX_RIGTH        (5*12 + 0)

#define iKEY_INDEX_SPACE         (iMATRIX_ROW_NUM*6 + 0)

//-----------------------------------------------------------------------------;
//配置区
//
#define MATRX_R                 IOA
#define USB_5V_PIN              PF7

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//
extern unsigned char const flash_key_win_tbl[];

//-----------------------------------------------------------------------------;
// 外部函数引用
//

//=============================================================================;
// 内部定义外部部引用区                                                        ;
//=============================================================================;
extern USBD_U16                 ukey_ctrl;
//{
    #define key_ctrl            ukey_ctrl.u16

    #define bkey_decode_valid   ukey_ctrl.BIT.b15
    #define bdir_wasd_status    ukey_ctrl.BIT.b14
    #define bkey_press          ukey_ctrl.BIT.b13
    #define bled_bright_en      ukey_ctrl.BIT.b12
    #define bwin_lock_status    ukey_ctrl.BIT.b10
    #define bdir_type_key       ukey_ctrl.BIT.b9
    #define bkey_press_status   ukey_ctrl.BIT.b8
    #define bbat_press_bak      ukey_ctrl.BIT.b7
    #define bbat_press          ukey_ctrl.BIT.b6
    #define bfn_save_flash      ukey_ctrl.BIT.b5
    #define bfn_key_status      ukey_ctrl.BIT.b4
//}
extern USBD_U16                 ukey_ctrl_ex;
//{
    #define key_ctrl_ex         ukey_ctrl_ex.u16

    #define boption_count       ukey_ctrl_ex.BIT.b15
    #define boption_count_bak   ukey_ctrl_ex.BIT.b14

    #define brgb_off_bak        ukey_ctrl_ex.BIT.b9
    #define brgb_off            ukey_ctrl_ex.BIT.b8

    #define bkey_all_realse     ukey_ctrl_ex.BIT.b7
    #define bfn_lock_status     ukey_ctrl_ex.BIT.b6
    #define bled_change         ukey_ctrl_ex.BIT.b5
    #define busb_suspend_bak    ukey_ctrl_ex.BIT.b4
    #define b24g_bt_conn_ok     ukey_ctrl_ex.BIT.b3
    #define bdefault_led_press  ukey_ctrl_ex.BIT.b0
//}

extern USBD_U8                  ukey_temp_flag;
//{
    #define key_temp_flag       ukey_temp_flag.u8

    #define bkey_temp5          ukey_temp_flag.BIT.b7
    #define bkey_temp4          ukey_temp_flag.BIT.b6
    #define bkey_temp3          ukey_temp_flag.BIT.b5
    #define bkey_temp2          ukey_temp_flag.BIT.b4
    #define bkey_temp1          ukey_temp_flag.BIT.b3
    #define bkey_temp0          ukey_temp_flag.BIT.b2
//}

extern USBD_U8                  ukey_temp_delay;
//{
    #define key_temp_delay      ukey_temp_delay.u8

    #define bkey_delay7         ukey_temp_delay.BIT.b7
    #define bkey_delay6         ukey_temp_delay.BIT.b6
    #define bkey_delay5         ukey_temp_delay.BIT.b5
    #define bkey_delay4         ukey_temp_delay.BIT.b4
    #define bkey_delay3         ukey_temp_delay.BIT.b3
    #define bkey_delay2         ukey_temp_delay.BIT.b2
    #define bkey_delay1         ukey_temp_delay.BIT.b1
    #define bkey_delay0         ukey_temp_delay.BIT.b0
//}

extern USBD_U16                 uspecial_key;
//{
    #define special_key         uspecial_key.u16

    #define bkey_led_dir        uspecial_key.BIT.b15
    #define bled_off            uspecial_key.BIT.b14
    #define bwin_lock           uspecial_key.BIT.b13
    #define bkey_rgb_cyc        uspecial_key.BIT.b12
    #define bkey_speed_up       uspecial_key.BIT.b11
    #define bkey_speed_dn       uspecial_key.BIT.b10
    #define bkey_light_up       uspecial_key.BIT.b9
    #define bkey_light_dn       uspecial_key.BIT.b8

    #define bkey_mode_cyc       uspecial_key.BIT.b7
    #define bkey_dir_wasd       uspecial_key.BIT.b5
    #define bfn_press           uspecial_key.BIT.b4
    #define bkey_test_press     uspecial_key.BIT.b3
//}

USBD_U16                        uspecial_key_bak;
//{
    #define special_key_bak     uspecial_key_bak.u16

    #define bkey_led_dir_bak    uspecial_key_bak.BIT.b15
    #define bled_off_back       uspecial_key_bak.BIT.b14
    #define bwin_lock_bak       uspecial_key_bak.BIT.b13
    #define bkey_rgb_cyc_bak    uspecial_key_bak.BIT.b12
    #define bkey_speed_up_bak   uspecial_key_bak.BIT.b11
    #define bkey_speed_dn_bak   uspecial_key_bak.BIT.b10
    #define bkey_light_up_bak   uspecial_key_bak.BIT.b9
    #define bkey_light_dn_bak   uspecial_key_bak.BIT.b8

    #define bkey_mode_cyc_bak   uspecial_key_bak.BIT.b7
    #define bkey_dir_wasd_bak   uspecial_key_bak.BIT.b5
    #define bfn_press_bak       uspecial_key_bak.BIT.b4
    #define bkey_test_up_bak    uspecial_key_bak.BIT.b3
//}
extern USBD_U8                  udevice_key;
//{
    #define device_key          udevice_key.u8

    #define bkey_24g_press      udevice_key.BIT.b6
    #define bkey_bt4_press      udevice_key.BIT.b5
    #define bkey_bt3_press      udevice_key.BIT.b4
    #define bkey_bt2_press      udevice_key.BIT.b3
    #define bkey_bt1_press      udevice_key.BIT.b2
    #define bkey_bt0_press      udevice_key.BIT.b1
    #define bkey_usb_press      udevice_key.BIT.b0
//}
extern USBD_U8                  udevice_key_bak;
//{
    #define device_key_bak      udevice_key_bak.u8
	
    #define bkey_24g_press_bak  udevice_key_bak.BIT.b6
    #define bkey_bt4_press_bak  udevice_key_bak.BIT.b5
    #define bkey_bt3_press_bak  udevice_key_bak.BIT.b4
    #define bkey_bt2_press_bak  udevice_key_bak.BIT.b3
    #define bkey_bt1_press_bak  udevice_key_bak.BIT.b2
    #define bkey_bt0_press_bak  udevice_key_bak.BIT.b1
    #define bkey_usb_press_bak  udevice_key_bak.BIT.b0
//}
extern unsigned char            decode_data_l_n;
extern unsigned char            decode_data_h_n;

extern unsigned char            matrix_status[];
extern unsigned char            define_key_fifo[];
extern unsigned char            key_fn_status[];
//{
    #define iNULL_MATRIX        0
    #define iNORMAL_MATRIX      1
    #define iFN_MATRIX          2
//}
extern unsigned char            mouse_data_key;
extern unsigned int             mouse_data_x;
extern unsigned int             mouse_data_y;
extern unsigned char            mouse_data_z;

extern unsigned char            std_key[];
extern unsigned char            multi_key[];
extern unsigned char            gKeyScan_bak[];
extern unsigned char            gKey_delay[];
#define gtemp                   gKey_delay
extern unsigned char            device_type_bak;

extern unsigned char            multi_data_tmp_l;
extern unsigned char            multi_data_tmp_h;
extern unsigned char            tmp_std_key[22];
extern unsigned char            rf_channel;

#define key_data_tmp            tmp_std_key
#define modifier_key_tmp        tmp_std_key[0]
#define key_data_tmp_1          tmp_std_key[1]
#define key_data_tmp_2          tmp_std_key[2]
#define key_data_tmp_3          tmp_std_key[3]
#define key_data_tmp_4          tmp_std_key[4]
#define key_data_tmp_5          tmp_std_key[5]
#define key_data_tmp_6          tmp_std_key[6]

//-----------------------------------------------------------------------------;
// 内部函数引用
//
extern void key_process(void);
extern void matrixkey_scan(void);
extern unsigned char scan_mode_swtich(void);
extern void mode_swtich_init(void);
extern void mode_swtich(unsigned char delay_en);
//
//-----------------------------------------------------------------------------;
#endif
