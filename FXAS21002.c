/*
 *  FXAS21002.c
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Version: 0.1
 *  Description: Very basic I2C FXAS21002 driver.
 *
 *  Notes:
 *      Initially written for Texas Instruments MSP-EXP432P401R Development Board
 *      Assumes I2C functions exist as below:
 *           void I2C_ReadMultipleRegisters(uint8_t addr, uint8_t regbase, uint8_t rxbytes);
 *           uint8_t I2C_ReadRegister(uint8_t addr, uint8_t reg);
 *           void I2C_WriteRegister(uint8_t addr, uint8_t reg, uint8_t data);
 *      Assumes I2C receive buffer exists somewhere (rxbuf)
 *      Provides no error checking
 */


#include "FXAS21002.h"
#include "i2c.h"

extern uint8_t rxbuf[13];

uint8_t FXAS_Init(void)
{
    if(FXAS_ExistsOn())
    {
        FXAS_Resolution(DPS2000); //Set resolution to 2000dps
        FXAS_Active(ODR800); //Update data at 800Hz
        return 1;
    } else
    {
        return 0;
    }
}

uint8_t FXAS_GetUpdate(FXASDATA *dps)
{
    I2C_ReadMultipleRegisters(FXAS_I2C_ADDR, FXAS_STATUS_REG, 7);
    if(rxbuf[0] & FXAS_DR_STATUS_ZYXDR)
    {
        dps->xdps = (int16_t) ((rxbuf[1] << 8) | rxbuf[2]);
        dps->ydps = (int16_t) ((rxbuf[3] << 8) | rxbuf[4]);
        dps->zdps = (int16_t) ((rxbuf[5] << 8) | rxbuf[6]);
        dps->xdps *= FXAS_2000DPS_LSB; //TODO: Implement config structure and process outside of update function
        dps->ydps *= FXAS_2000DPS_LSB;
        dps->zdps *= FXAS_2000DPS_LSB;
    }
    return 1;
}

uint8_t FXAS_SetMode(MODE_t m, ODR_t dr)
{
    switch(m)
    {
    case MODE_STANDBY:    I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_STANDBY); break;
    case MODE_READY:      I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_READY); break;
    case MODE_ACTIVE:     FXAS_Active(dr); break;
    }
    return 1;
}

uint8_t FXAS_Active(ODR_t dr)

{
    switch(dr)
    {
    case ODR0125:  I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_6); break;
    case ODR25:    I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_5); break;
    case ODR50:    I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_4); break;
    case ODR100:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_3); break;
    case ODR200:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_2); break;
    case ODR400:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_1); break;
    case ODR800:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG1, FXAS_CTRL_REG1_ACTIVE|FXAS_CTRL_REG1_DR_0); break;
    }
    return 1;
}

uint8_t FXAS_Resolution(DPS_t res)
{
    switch(res)
    {
    case DPS250:    I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG0, FXAS_CTRL_REG0_FS_3); break;
    case DPS500:    I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG0, FXAS_CTRL_REG0_FS_2); break;
    case DPS1000:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG0, FXAS_CTRL_REG0_FS_1); break;
    case DPS2000:   I2C_WriteRegister(FXAS_I2C_ADDR, FXAS_CTRL_REG0, FXAS_CTRL_REG0_FS_0); break;
    }
    return 1;
}

uint8_t FXAS_ExistsOn(void)
{
    if(I2C_ReadRegister(FXAS_I2C_ADDR, FXAS_WHO_AM_I) == FXAS_IDENT)
    {
    if(I2C_ReadRegister(FXAS_I2C_ADDR, FXAS_INT_SRC_FLAG) & FXAS_INT_SRC_FLAG_BOOTEND)
        {
        return 1;
        } else
        {
        return 0;
        }
    } else
    {
        return 0;
    }
}

