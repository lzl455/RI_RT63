/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: led.h
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#ifndef _LED_LOGO_H_
#define _LED_LOGO_H_

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;
#define iLED_SNAKE              (15*5)

//-----------------------------------------------------------------------------;
// 配置常量定义区
//
#define iPWM_R                  0x01
#define iPWM_G                  0x02
#define iPWM_B                  0x04
#define iPWM_W                  0x0F

#define iRGB_INVLAID            0xFF

#define iPWM_MAX                128
#define iPWM_SNAKE_MAX          126

#define iRGB_INDEX_MAX          7
#define iRGB_QICAI              7

#define iLED_MAX_BHQF           76
#define iLFSR_MULTINOMIAL       0xF521

//-----------------------------------------------------------------------------;
//配置区
//
#define PWM_G_0                 PWM102DL
#define PWM_B_0                 PWM101DL
#define PWM_R_0                 PWM100DL
#define PWM_R_0_PIN             PB0

#define PWM_G_1                 PWM105DL
#define PWM_B_1                 PWM104DL
#define PWM_R_1                 PWM103DL
#define PWM_R_1_PIN             PB3

#define PWM_G_2                 PWM108DL
#define PWM_B_2                 PWM107DL
#define PWM_R_2                 PWM106DL

#define PWM_G_3                 PWM111DL
#define PWM_B_3                 PWM110DL
#define PWM_R_3                 PWM109DL
#define PWM_R_3_PIN             PC1

#define PWM_G_4                 PWM114DL
#define PWM_B_4                 PWM113DL
#define PWM_R_4                 PWM112DL
#define PWM_R_4_PIN             PC4

#define PWM_G_5                 PWM117DL
#define PWM_B_5                 PWM116DL
#define PWM_R_5                 PWM115DL

#define PWM_C0_LOW              PD0=0
#define PWM_C1_LOW              PD1=0
#define PWM_C2_LOW              PD2=0
#define PWM_C3_LOW              PD3=0
#define PWM_C4_LOW              PD4=0
#define PWM_C5_LOW              PD5=0
#define PWM_C6_LOW              PD6=0
#define PWM_C7_LOW              PD7=0
#define PWM_C8_LOW              PE0=0
#define PWM_C9_LOW              PE1=0
#define PWM_C10_LOW             PE2=0
#define PWM_C11_LOW             PE3=0
#define PWM_C12_LOW             PE4=0
#define PWM_C13_LOW             PE5=0
#define PWM_C14_LOW             PE6=0

#define PWM_C0_HIGH             PD0=1
#define PWM_C1_HIGH             PD1=1
#define PWM_C2_HIGH             PD2=1
#define PWM_C3_HIGH             PD3=1
#define PWM_C4_HIGH             PD4=1
#define PWM_C5_HIGH             PD5=1
#define PWM_C6_HIGH             PD6=1
#define PWM_C7_HIGH             PD7=1
#define PWM_C8_HIGH             PE0=1
#define PWM_C9_HIGH             PE1=1
#define PWM_C10_HIGH            PE2=1
#define PWM_C11_HIGH            PE3=1
#define PWM_C12_HIGH            PE4=1
#define PWM_C13_HIGH            PE5=1
#define PWM_C14_HIGH            PE6=1

#define mPWM_POWER_ON           PC7=0
#define mPWM_POWER_OFF          PC7=1

//-----------------------------------------------------------------------------;
// 配置区
//
enum led_mod
{
    iMODE_LED_OFF       =0,
    iMODE_LED_ON        =1,
    iMODE_LED_BREATH    =2,
    iMODE_LED_SNAKE     =3,
    iMODE_LED_NHJB      =4,                     // 霓虹渐变
    iMODE_LED_SINGLE    =5,                     // 踏雪无痕
    iMODE_LED_LG_L_R    =6,
    iMODE_LED_LXGY      =7,                     // 流星赶月
    iMODE_LED_STAR      =8,                     // 繁星点点
    iMODE_LED_SBZL      =9,                    // 随波逐流
    iMODE_LED_ZXB       =10,                    // 正玄波
    iMODE_LED_YZMB      =11,                    // 雨中漫步
    iMODE_LED_CHLP      =12,                    // 彩虹轮盘
    iMODE_LED_BHQF      =13,                    // 百花齐放
    iMODE_LED_ARROW     =14,                    // 箭头
    iMODE_LED_CENTRE    =15,                    // 中心

    iMODE_LED_DEF       =16,                    // 自定义

    iMODE_LED_MAX       =16,
    iMODE_LED_INVALID   =17,
    iMODE_LED_RED       =18,                    // 红色
    iMODE_LED_GREEN     =19,                    // 绿色
    iMODE_LED_BLUE      =20,                    // 蓝色
};
enum led_level
{
    iLED_LEV_MIN=0,// 最暗
    iLED_LEV_0 = 0,
    iLED_LEV_1 = 1,
    iLED_LEV_2 = 2,
    iLED_LEV_3 = 3,
    iLED_LEV_4 = 4,
    iLED_LEV_MAX = 4,	// 最亮
    iLED_LEV_MAX_LVD = 2,// 最亮
};

enum speed_level
{
    iSPEED_LEV_MIN = 0,
    iSPEED_LEV_1 = 0,
    iSPEED_LEV_2 = 1,
    iSPEED_LEV_3 = 2,
    iSPEED_LEV_4 = 3,
    iSPEED_LEV_5 = 4,
    iSPEED_LEV_MAX = 4,
};

//=============================================================================;
// 外部定义内部引用区                                                          ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 外部寄存器引用
//
//-----------------------------------------------------------------------------;
// 外部函数引用
//
extern unsigned char    const   led_liuguang_l_r_tbl[];
extern unsigned char    const   led_liuguang_rgb_tbl[];

extern unsigned char    const   lxgy_r_tbl[6];
extern unsigned char    const   lxgy_g_tbl[6];
extern unsigned char    const   lxgy_b_tbl[6];
extern unsigned char    const   lxgy_ctrl_tbl[6];

//=============================================================================;
// 内部定义外部引用区      
//=============================================================================;

//-----------------------------------------------------------------------------;
// 寄存器引用
//
extern USBD_U16                 uled_ctrl_reg;
//{
    #define led_ctrl_reg        uled_ctrl_reg.u16

    #define bled_hint_ing       uled_ctrl_reg.BIT.b13
    #define bled_run_dir        uled_ctrl_reg.BIT.b11 // 方向：0：左→右；1：右→左；
    #define brgb_bright_en      uled_ctrl_reg.BIT.b10
    #define bsave_flash         uled_ctrl_reg.BIT.b8

    #define bsave_6621d         uled_ctrl_reg.BIT.b7
    #define bdelay_time         uled_ctrl_reg.BIT.b6
    #define bmode_swtich_hint   uled_ctrl_reg.BIT.b4
    #define bled_mode_single    uled_ctrl_reg.BIT.b2
    #define bback_led_status    uled_ctrl_reg.BIT.b0
//}
extern USBD_U8                  urgb_enable;
//{
    #define rgb_enable          urgb_enable.u8
    #define bw_enable           urgb_enable.BIT.b3
    #define bb_enable           urgb_enable.BIT.b2
    #define bg_enable           urgb_enable.BIT.b1
    #define br_enable           urgb_enable.BIT.b0
//}
extern USBD_U16                 uled_status_reg;
//{
    #define led_status_reg      uled_status_reg.u16
    #define bled15_status       uled_status_reg.BIT.b15
    #define bled14_status       uled_status_reg.BIT.b14
    #define bled13_status       uled_status_reg.BIT.b13
    #define bled12_status       uled_status_reg.BIT.b12
    #define bled11_status       uled_status_reg.BIT.b11
    #define bled10_status       uled_status_reg.BIT.b10
    #define bled9_status        uled_status_reg.BIT.b9
    #define bled8_status        uled_status_reg.BIT.b8
    #define bled7_status        uled_status_reg.BIT.b7
    #define bled6_status        uled_status_reg.BIT.b6
    #define bled5_status        uled_status_reg.BIT.b5
    #define bled4_status        uled_status_reg.BIT.b4
    #define bled3_status        uled_status_reg.BIT.b3
    #define bled2_status        uled_status_reg.BIT.b2
    #define bled1_status        uled_status_reg.BIT.b1
    #define bled0_status        uled_status_reg.BIT.b0
//}
extern USBD_U8                  uled_status_reg_ex;
//{
    #define led_status_reg_ex   uled_status_reg_ex.u8

    #define bled18_status       uled_status_reg_ex.BIT.b2
    #define bled17_status       uled_status_reg_ex.BIT.b1
    #define bled16_status       uled_status_reg_ex.BIT.b0
//}

extern USBD_U8                  uled_use_flag;
//{
    #define led_use_flag        uled_use_flag.u8

    #define bled_7_idle         uled_use_flag.BIT.b7
    #define bled_6_idle         uled_use_flag.BIT.b6
    #define bled_5_idle         uled_use_flag.BIT.b5
    #define bled_4_idle         uled_use_flag.BIT.b4
    #define bled_3_idle         uled_use_flag.BIT.b3
    #define bled_2_idle         uled_use_flag.BIT.b2
    #define bled_1_idle         uled_use_flag.BIT.b1
    #define bled_0_idle         uled_use_flag.BIT.b0
//}
extern unsigned char            pwm_value;

extern unsigned char            pwm_time_count;
extern unsigned char            led_delay_count;

extern unsigned int             delay_time_count;
extern unsigned char            rgb_index;
extern unsigned char            rgb_enable_bak;

extern enum led_mod             led_cur_mode;
extern enum led_mod             led_pre_mode;
extern enum led_level           led_light_lev;
extern enum speed_level         led_speed_lev;
extern unsigned char            led_rgb_index;

extern unsigned char            led_index_value;
extern unsigned char            led_scan_count;
extern enum led_level           led_light_value;

extern unsigned char            pwm_r_array[];
extern unsigned char            pwm_g_array[];
extern unsigned char            pwm_b_array[];

extern unsigned char            pwm_duty_array_0[];
extern unsigned char            pwm_duty_array_1[];
extern unsigned char            pwm_duty_array_2[];
extern unsigned char            pwm_duty_array_3[];

extern unsigned char            snake_led_index;
extern unsigned char            nhjb_led_index;
extern unsigned int             lfsr_value;
extern unsigned char            flash_updata_delay;
extern unsigned char            scan_index;
extern unsigned char            back_led_off_delay;
extern unsigned char            save_6621d_delay;

extern unsigned int             mode_swtich_time_count;
extern unsigned int             rf_delay_time_count;

extern unsigned char    const   led_snake_table[];
extern unsigned char    const   rgb_en_tbl[];
extern unsigned char    const   rgb_time_delay[];

extern unsigned char    const   sbzl_rgb_tbl[];
extern unsigned char    const   sbzl_r_tbl[];
extern unsigned char    const   sbzl_g_tbl[];
extern unsigned char    const   sbzl_b_tbl[];
extern unsigned char    const   sbzl_ctrl_tbl[];

extern unsigned char    const   chlp_r_tbl[];
extern unsigned char    const   chlp_g_tbl[];
extern unsigned char    const   chlp_b_tbl[];
extern unsigned char    const   chlp_ctrl_tbl[];
extern unsigned char    const   led_to_matrix_tab_1[];
extern unsigned char    const   led_to_matrix_tab_2[iLED_COL_NUM][iLED_ROW_NUM];
extern unsigned char    const   matrix_to_led_tab[];
extern unsigned char    const   led_to_matrix_tab_3[];
extern unsigned char    const   led_def_tbl[];
extern enum led_mod led_cur_mode_bak;
extern unsigned int led_hint_time_count;
extern unsigned int low_hint_time;
//-----------------------------------------------------------------------------;
// 函数引用
//

/*******************************************************************************
 led_process: 
*******************************************************************************/

extern void led_hint(void);
extern void pwm2_init(void);
extern void device_led_on(void);
extern void device_led_off(void);
extern void led_process(void);
//extern void clr_all_rgb(void);
#define clr_all_rgb     clr_rgb

extern void clr_rgb(void);
extern void set_rgb(void);
extern void rgb_pwm0_w(void);
extern void rgb_w_max(void);
extern void rgb_pwm012_w(void);

extern void led_mode_on(void);
extern void led_mode_breath(void);
extern void led_mode_snake(void);
extern void led_mode_single(void);
extern void led_mode_nhjb(void);
extern void led_mode_liuguang_l_r(void);
extern void led_mode_lxgy(void);
extern void led_mode_star(void);

extern void led_mode_jg_init(unsigned char led_c);
extern void led_mode_jiguang(void);

extern void led_mode_bolang(void);
extern void led_mode_sbzl(void);
extern void led_mode_zxb(void);
extern void led_mode_yzmb(void);
extern void led_mode_chlp(void);
extern void led_mode_bhqf(void);
extern void led_mode_arrow(void);
extern void led_mode_centre(void);
extern void led_mode_def(void);

extern void bevel_process(void);
extern void left_right_process(void);
extern void ripple_process(void);

extern void timer_int_process(void);
//
//-----------------------------------------------------------------------------;
#endif
