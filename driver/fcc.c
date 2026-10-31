/*******************************************************************************
* Copyright (c) 2013, SHENZHEN SEMITEK Co.,LTD.
* All rights reserved.
*
* 文件名称: uart.c
*
* 功能说明: 
FCC进入方法：
蓝牙模式：
FN+1按下1s进入组合对码模式(对码状态灯闪烁，FN+1不要松开)，这时再按下“↓”键1s，再松开所有按键进入FCC测试模式
进入测试模式，↓对应的灯常亮
蓝牙模式通过←按键对应的灯做提示
2.4G模式：
FN+4按下1s进入组合对码模式(对码状态灯闪烁，FN+4不要松开)，这时再按下“↓”键1s，再松开所有按键进入FCC测试模式
进入测试模式，↓对应的灯常亮
2.4G模式通过→按键对应的灯做提示
进入测试模式后，通过↓按键切换测试状态

  A6 82  进入FCC
  A6 81 切BLE
  A6 80 切2.4G

FCC状态切换：
按一下状态切换按键，对应状态灯做相应的提示，例如闪1次就是模式1，闪2次就是模式2
模式1：LED闪烁1次--空载波持续发射--2402MHz
模式2：LED闪烁2次--空载波持续发射--2440MHz
模式3：LED闪烁3次--空载波持续发射--2480MHz

模式4：LED闪烁4次--调制波持续发射--2402MHz
模式5：LED闪烁5次--调制波持续发射--2440MHz
模式6：LED闪烁6次--调制波持续发射--2480MHz

模式7：LED闪烁7次--接收模式--2402MHz
模式8：LED闪烁8次--接收模式--2440MHz
模式9：LED闪烁9次--接收模式--2480MHz

模式10：LED闪烁10次--跳频发射模式--2402MHz~2480MHz
*******************************************************************************/
#include "..\defines.h"

//=============================================================================;
// 配置引用区                                                                  ;
//=============================================================================;

//-----------------------------------------------------------------------------;
// 表格定义区
//
#define iSWITCH_R               (1<<2)
#define iSWITCH_C               14              // →

#define iFCC_BT0_R              (1<<3)
#define iFCC_BT0_C              2               // Z

#define iFCC_24G_R              (1<<3)
#define iFCC_24G_C              6               // B

#define iFCC_FN_R               (1<<2)
#define iFCC_FN_C               10              // FN

//=============================================================================;
// 代码区                                                                      ;
//=============================================================================;
extern void fcc_cmd_tx(unsigned char cmd);

/******************************************************************************
* 函数名称: get_bat_value()
* 功能描述:
* 参    数: A6 82 进入FCC
            A6 81 切BLE
            A6 80 切2.4G
* 说    明:
******************************************************************************/
void fcc_test_process(void)
{
    unsigned char i, cmd, led_count;

    if(iFCC_FN_R != matrix_status[iFCC_FN_C])
        return;

    if(iFCC_BT0_R == matrix_status[iFCC_BT0_C])
        cmd = iCTRL_CMD_FCC_BLE;
    else if(iFCC_24G_R == matrix_status[iFCC_24G_C])
        cmd = iCTRL_CMD_FCC_24G;
    else
        return;

    if(iSWITCH_R != matrix_status[iSWITCH_C])
        return;

    fcc_cmd_tx(iCTRL_CMD_FCC);                  // 进入测试模式
	clr_rgb();

    delayms(10);
    pwm_r_array[iKEY_INDEX_DOWN] = iPWM_MAX;

    while(1)
    {
check_key_relase:
        if(bkey_scan)
        {
            bkey_scan = 0;
            for(i = 0; i<iMATRIX_COL_NUM; i++)
            {
                if(0 != matrix_status[i])
                    goto check_key_relase;
            }
            break;
        }
    }
    delayms(200);

    led_count = 0;

    while(1)
    {
        if(bkey_scan)
        {
            bkey_scan = 0;
            if(iSWITCH_R == matrix_status[iSWITCH_C])
            {
                if(!btemp_bit0)
                {
                    btemp_bit0 = 1;
                    fcc_cmd_tx(cmd);

                    led_count++;
                    if(10<led_count)
                        led_count = 1;
                    for(i=0; i<led_count; i++)
                    {
                        if(iCTRL_CMD_FCC_BLE == cmd)
                            pwm_r_array[iKEY_INDEX_LEFT] = iPWM_MAX;
                        else //if(iCTRL_CMD_FCC_24G == cmd)
                            pwm_r_array[iKEY_INDEX_RIGTH] = iPWM_MAX;
                        delayms(200);

                        pwm_r_array[iKEY_INDEX_LEFT] = 0;
                        pwm_r_array[iKEY_INDEX_RIGTH] = 0;
                        delayms(200);
                    }
                }
            }
            else
            {
                btemp_bit0 = 0;
            }
        }
    }
}