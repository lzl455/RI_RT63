/*******************************************************************************
* Copyright (c) 2022, SHENZHEN BEIHAI Co.,LTD.
* All rights reserved.
*
* 文件名称: Flash_process.c
*
* 功能说明:
* 修改说明:
*******************************************************************************/
#include "..\defines.h"

extern unsigned char    const   matrixkey_win_tbl[];

//-----------------------------------------------------------------------------;
// 常量定义区
//
unsigned char                   s_para_tbl[16];
unsigned char                   device_para_tbl[2];
//-----------------------------------------------------------------------------;
// 变量定义区
//
unsigned char                   cfg_base;

//-----------------------------------------------------------------------------;
// 内部宏定义区
//

void led_default_load(void)
{
    s_usb_led_mode = iMODE_LED_SBZL|(iRGB_QICAI<<5);
    s_usb_led_para = iLED_LEV_4|(iSPEED_LEV_1<<4);
    s_rgb_mode = iLED_ENABLE;
}

/*******************************************************************************
* 函数名称: checksum_check()
* 功能描述:
* 输入参数:无
* 输出参数:无
* 说    明:
*******************************************************************************/
unsigned char checksum_flash(unsigned char lenght, unsigned char const *ptr)
{
    unsigned char i, check;

    check = 0x5A;
    for(i=0; i<lenght; i++)
    {
        check ^= ptr[i];
    }

    return check;
}

void memcpy_const(unsigned char *ptr_d, unsigned char const *ptr_s, unsigned char lenght)
{
    for(unsigned char i=0; i<lenght; i++)
    {
        *ptr_d = *ptr_s;
        ptr_d++;
        ptr_s++;
    }
}

void memcpy(unsigned char  *ptr_d, unsigned char *ptr_s, unsigned char lenght)
{
    for(unsigned char i=0; i<lenght; i++)
    {
        *ptr_d = *ptr_s;
        ptr_d++;
        ptr_s++;
    }
}

void memset(unsigned char  *ptr_d, unsigned char const dat, unsigned char lenght)
{
    for(unsigned char i=0; i<lenght; i++)
    {
        *ptr_d = dat;
        ptr_d++;
    }
}

/*******************************************************************************
* 函数名称: cfg_load
* 功能描述:
* 输入参数: 无
* 输出参数:
* 说    明:
*******************************************************************************/
void cfg_load(void)
{
    unsigned char i,j,k;
//----------------------------------------------------------------------------
// KEY MODE0  KEY0~KEY63
//
    bwrite_flash = 0;
    j = 0xF0;
    k = 0;
    for(i=0x00; i<0x80;)
    {
        gtemp[k] = checksum_flash(16, flash_key_win_tbl + i);
        if(flash_key_win_tbl[j++] != gtemp[k])
        {
            bwrite_flash = 1;
            memcpy_const(flash_dat+i, matrixkey_win_tbl+i, 16);
        }
        else
        {
            memcpy_const(flash_dat+i, flash_key_win_tbl+i, 16);
        }
        k++;
        i += 16;
    }

    if(bwrite_flash)
    {
        flash_program(0x00, 128);
        memcpy(flash_dat, gtemp, 8);
        flash_program(0xF0, 8);
	}
//----------------------------------------------------------------------------
// KEY MODE0  KEY64~KEY119
//
    bwrite_flash = 0;
    j = 0xF8;
    k = 0;
    for(i=0x80; i<0xF0;)
    {
        gtemp[k] = checksum_flash(16, flash_key_win_tbl + i);
        if(flash_key_win_tbl[j++] != gtemp[k])
        {
            bwrite_flash = 1;
            memcpy_const(flash_dat+(i&0x7F), matrixkey_win_tbl+i, 16);
        }
        else
        {
            memcpy_const(flash_dat+(i&0x7F), flash_key_win_tbl+i, 16);
        }
        k++;
        i += 16;
    }

    if(bwrite_flash)
    {
        flash_program(0x80, 112);
        memcpy(flash_dat, gtemp, 7);
        flash_dat[7] = 0xA5;
        flash_program(0xF8, 8);
    }
//----------------------------------------------------------------------------
// LED CFG
//
    bwrite_flash = 0;
    gtemp[0] = checksum_flash(254, led_def_tbl);
	if(led_def_tbl[iLED_CS_ADDR] != gtemp[0])
	{
        memset(flash_dat, 0x00, 128);
		flash_dat[iKEY_INDEX_W*2] = 0x1F;
		flash_dat[iKEY_INDEX_A*2] = 0x1F;
		flash_dat[iKEY_INDEX_S*2] = 0x1F;
		flash_dat[iKEY_INDEX_D*2] = 0x1F;
        flash_program(iLED_CFG_BASE_ADDR+0x00, 128);

        memset(flash_dat, 0x00, 128);
        flash_dat[126] = 0xA5;
        flash_dat[127] = 0xA5;
        flash_program(iLED_CFG_BASE_ADDR+0x80, 128);
	}

//----------------------------------------------------------------------------
// CFG INFO
//
    cfg_base = 0x7C;
    while(1)
    {
        device_para_tbl[0] = flash_bank_15[cfg_base+0];
        device_para_tbl[1] = flash_bank_15[cfg_base+1];

        if(iPARA_TYPE == (s_mode&iPARA_TYPE_MASK))
            break;

        if(0 == cfg_base)
        {
	        s_mode = iDEVICE_TYPE_BT0;
	        s_bt_index = iDEVICE_TYPE_BT0;
	        cfg_base = 0xFF;
            break;
        }

        cfg_base &= 0xFC;
        cfg_base -= 0x04;
    }

    sys_ctrl_reg &= 0xF0;
    sys_ctrl_reg |= (s_mode&0x0F);
    //bt_index = (s_bt_index&iBT_INDEX_MASK);

    lfsr_value = 0x55AA;
}

/*******************************************************************************
* 函数名称: e2_config_load
* 功能描述:
* 输入参数: 无
* 输出参数:
* 说    明:
*******************************************************************************/
void load_led_para(void)
{
    if(iPARA_TYPE != (s_para&iPARA_TYPE_MASK))
    {
        s_para = 0xA0|iWIN_MODE;
	    led_default_load();
	}
    //bwin_lock_status = 0;
    //if(s_para&iWIN_LOCK)
        //bwin_lock_status = 1;

    bwin_mac_sataus = 0;
    if(s_para&iWIN_MODE)
        bwin_mac_sataus = 1;

    bdir_wasd_status = 0;
    if(s_para&iDIR_LOCK)
        bdir_wasd_status = 1;

    //rgb_cur_mode = (s_rgb_mode&iRGB_MODE_MASK);
    //brgb_bright_en = 0;
    //if(s_rgb_mode&iRGB_ENABLE)
        //brgb_bright_en = 1;

    //bled_bright_en = 0;
	//if(s_rgb_mode&iLED_ENABLE)
	    bled_bright_en = 1;

    bled_run_dir = 0;
    if(s_rgb_mode&iLED_DIR)
        bled_run_dir = 1;

    if(bconn_type_usb)
    {
        device_type = iCTRL_CMD_IDLE;
    }
    else
    {
        switch(sys_ctrl_reg&0x07)
        {
            case iDEVICE_TYPE_BT0:
                device_type = iCTRL_CMD_BT0;

                break;
            case iDEVICE_TYPE_BT1:
                device_type = iCTRL_CMD_BT1;

                break;
            case iDEVICE_TYPE_BT2:
                device_type = iCTRL_CMD_BT2;

                break;
            default:
                device_type = iCTRL_CMD_24G;

                break;
        }
    }

    led_cur_mode = (s_usb_led_mode&iMODE_MASK);
    led_light_lev = (s_usb_led_para&iLEV_MASK);
    led_speed_lev = ((s_usb_led_para>>4)&iLEV_MASK);
    led_rgb_index = (s_usb_led_mode>>5);
}

/*******************************************************************************
* 函数名称: e2_config_load
* 功能描述:
* 输入参数: 无
* 输出参数:
* 说    明:
*******************************************************************************/
void e2_config_load(void)
{
    cfg_load();
	buart_flash_ok = 0;
	
	//bled_bright_en = 1;

    //led_light_lev = iLED_LEV_4;
    //led_speed_lev = iSPEED_LEV_5;
    //led_rgb_index = 6;
    //sys_ctrl_reg = iDEVICE_TYPE_USB;
	//sys_ctrl_reg = iDEVICE_TYPE_BT0;
}

/*******************************************************************************
* 函数名称: cfg_mode_save
* 功能描述:
* 输入参数: 无
* 输出参数:
* 说    明: 模式切换和开关背光保存在FLASH中
*******************************************************************************/
void cfg_mode_save(void)
{
    if(0xFF == cfg_base)
        cfg_base = 0;
    else
    {
        cfg_base += 4;
        if(0x7C<cfg_base)
            cfg_base = 0;
    }

    cfg_base &= 0x7C;
    s_mode = (sys_ctrl_reg&0x0F);
    s_mode |= 0xA0;
    s_bt_index = (0&iBT_INDEX_MASK);

    memset(flash_dat, 0x00, 128);
    flash_fifo[cfg_base+0] = s_mode;
    flash_fifo[cfg_base+1] = s_bt_index;

    flash_program(iCFG_ADDR, 128);
    cfg_load();
}

/*******************************************************************************
* 函数名称: cfg_6621d_save
* 功能描述:
* 输入参数: 无
* 输出参数:
* 说    明: LED灯效、亮度、速度、WIN锁定、系统参数到6621D
*******************************************************************************/
void cfg_6621d_save(void)
{
    s_para = 0xA0;
    if(bwin_lock_status)
        s_para |= iWIN_LOCK;
    if(bwin_mac_sataus)
        s_para |= iWIN_MODE;
    if(bdir_wasd_status)
        s_para |= iDIR_LOCK;

    s_rgb_mode = (0&iRGB_MODE_MASK);

    if(bled_bright_en)
        s_rgb_mode |= iLED_ENABLE;
    //if(brgb_bright_en)
        //s_rgb_mode |= iRGB_ENABLE;
    if(bled_run_dir)
        s_rgb_mode |= iLED_DIR;

    s_usb_led_mode = (led_cur_mode&0x1F);
	s_usb_led_mode |= ((led_rgb_index<<5)&0xE0);
    s_usb_led_para = (led_light_lev&iLEV_MASK);
    s_usb_led_para |= ((led_speed_lev<<4)&iSPEED_MASK);

    memcpy(om6621d_flash_dat, s_para_tbl, 16);

	bom6621d_flash_w = 1;
}
