/*
 * FXAS21002.h
 *
 *  Created on: Jun 1, 2017
 *  Author: Eric FitzSimon
 *  Description: Header for basic FXAS21002 driver.
 *  Version: 0.1
 */

#ifndef FXAS21002_H_
#define FXAS21002_H_

#include <msp.h>

typedef enum{
    ODR800,
    ODR400,
    ODR200,
    ODR100,
    ODR50,
    ODR25,
    ODR0125
} ODR_t; //Enumeration to simplify Output Data Rate

typedef enum{
    DPS2000,
    DPS1000,
    DPS500,
    DPS250,
} DPS_t; //Enumeration to simplify Degrees per Second Selection

typedef enum{
    MODE_ACTIVE,
    MODE_READY,
    MODE_STANDBY
} MODE_t; //Mode selection enumeration

typedef struct{
    int16_t xdps;
    int16_t ydps;
    int16_t zdps;
    float gx;
    float gy;
    float gz;
} FXASDATA; /* Structure type for FXAS output data and calculated values (to be used for conversion to radians)*/

uint8_t FXAS_Init(void);
uint8_t FXAS_Active(ODR_t dr);
uint8_t FXAS_ExistsOn(void);
uint8_t FXAS_Resolution(DPS_t res);
uint8_t FXAS_SetMode(MODE_t m, ODR_t dr);
uint8_t FXAS_GetUpdate(FXASDATA *dps);


#define FXAS_I2C_ADDR                           (uint8_t)(0x21) /* Set to proper address based on board configuration */
#define FXAS_IDENT                              (uint8_t)(0xD7) /* Value of WHO_AM_I Register */

#define FXAS_250DPS_LSB                         0.0078125f
#define FXAS_500DPS_LSB                         0.015625f
#define FXAS_1000DPS_LSB                        0.03125f
#define FXAS_2000DPS_LSB                        0.0625f

/* FXAS21002 Registers */
#define FXAS_STATUS_REG                         (uint8_t)(0x00) /* Alias for DR_STATUS or F_STATUS */
#define FXAS_OUT_X_MSB                          (uint8_t)(0x01) /* 8 MSBs of 16-bit X-axis data sample */
#define FXAS_OUT_X_LSB                          (uint8_t)(0x02) /* 8 LSBs of 16-bit X-axis data sample */
#define FXAS_OUT_Y_MSB                          (uint8_t)(0x03) /* 8 MSBs of 16-bit Y-axis data sample */
#define FXAS_OUT_Y_LSB                          (uint8_t)(0x04) /* 8 LSBs of 16-bit Y-axis data sample */
#define FXAS_OUT_Z_MSB                          (uint8_t)(0x05) /* 8 MSBs of 16-bit Z-axis data sample */
#define FXAS_OUT_Z_LSB                          (uint8_t)(0x06) /* 8 LSBs of 16-bit Z-axis data sample */
#define FXAS_DR_STATUS                          (uint8_t)(0x07) /* Data-ready status information */
#define FXAS_F_STATUS                           (uint8_t)(0x08) /* FIFO Status Register */
#define FXAS_F_SETUP                            (uint8_t)(0x09) /* FIFO Setup Register */
#define FXAS_F_EVENT                            (uint8_t)(0x0A) /* FIFO_Event Register */
#define FXAS_INT_SRC_FLAG                       (uint8_t)(0x0B) /* Interrupt event source status flags */
#define FXAS_WHO_AM_I                           (uint8_t)(0x0C) /* Device ID */
#define FXAS_CTRL_REG0                          (uint8_t)(0x0D) /* Control register 0 */
#define FXAS_RT_CFG                             (uint8_t)(0x0E) /* Rate threshold function configuration */
#define FXAS_RT_SRC                             (uint8_t)(0x0F) /* Rate threshold event flags status */
#define FXAS_RT_THS                             (uint8_t)(0x10) /* Rate threshold function threshold */
#define FXAS_RT_COUNT                           (uint8_t)(0x11) /* Rate threshold function debounce counter */
#define FXAS_TEMP                               (uint8_t)(0x12) /* Device Temperature Register */
#define FXAS_CTRL_REG1                          (uint8_t)(0x13) /* Control Register 1 */
#define FXAS_CTRL_REG2                          (uint8_t)(0x14) /* Control Register 2 */
#define FXAS_CTRL_REG3                          (uint8_t)(0x15) /* Control Register 3 */

/* FXAS_DR_STATUS Bits */
#define FXAS_DR_STATUS_XDR                      (uint8_t)(0x01) /* X-axis data ready bit */
#define FXAS_DR_STATUS_YDR                      (uint8_t)(0x02) /* Y-axis data ready bit */
#define FXAS_DR_STATUS_ZDR                      (uint8_t)(0x04) /* Z-axis data ready bit */
#define FXAS_DR_STATUS_ZYXDR                    (uint8_t)(0x08) /* XYZ-axes data ready bit */
#define FXAS_DR_STATUS_XOW                      (uint8_t)(0x10) /* X-axis data overwritten bit */
#define FXAS_DR_STATUS_YOW                      (uint8_t)(0x20) /* Y-axis data overwritten bit */
#define FXAS_DR_STATUS_ZOW                      (uint8_t)(0x40) /* Z-axis data overwritten bit */
#define FXAS_DR_STATUS_ZYXOW                    (uint8_t)(0x80) /* XYZ-axes data overwritten bit */

/* FXAS_F_STATUS Bits */

#define FXAS_F_STATUS_F_CNT0                    (uint8_t)(0x01) /* FIFO Sample counter bit 0 */
#define FXAS_F_STATUS_F_CNT1                    (uint8_t)(0x02) /* FIFO Sample counter bit 1 */
#define FXAS_F_STATUS_F_CNT2                    (uint8_t)(0x04) /* FIFO Sample counter bit 2 */
#define FXAS_F_STATUS_F_CNT3                    (uint8_t)(0x08) /* FIFO Sample counter bit 3 */
#define FXAS_F_STATUS_F_CNT4                    (uint8_t)(0x10) /* FIFO Sample counter bit 4 */
#define FXAS_F_STATUS_F_CNT5                    (uint8_t)(0x20) /* FIFO Sample counter bit 5 */
#define FXAS_F_STATUS_F_WMKF                    (uint8_t)(0x40) /* FIFO Watermark flag */
#define FXAS_F_STATUS_F_OVF                     (uint8_t)(0x80) /* FIFO overflow flag */

/* FXAS_F_SETUP Bits */

#define FXAS_F_SETUP_F_WMRK0                    (uint8_t)(0x01) /* FIFO Sample Count Watermark Setting Bit 0 */
#define FXAS_F_SETUP_F_WMRK1                    (uint8_t)(0x02) /* FIFO Sample Count Watermark Setting Bit 1 */
#define FXAS_F_SETUP_F_WMRK2                    (uint8_t)(0x04) /* FIFO Sample Count Watermark Setting Bit 2 */
#define FXAS_F_SETUP_F_WMRK3                    (uint8_t)(0x08) /* FIFO Sample Count Watermark Setting Bit 3 */
#define FXAS_F_SETUP_F_WMRK4                    (uint8_t)(0x10) /* FIFO Sample Count Watermark Setting Bit 4 */
#define FXAS_F_SETUP_F_WMRK5                    (uint8_t)(0x20) /* FIFO Sample Count Watermark Setting Bit 5 */
#define FXAS_F_SETUP_F_MODE0                    (uint8_t)(0x40) /* FIFO Operating Mode Selection Bit 0 */
#define FXAS_F_SETUP_F_MODE1                    (uint8_t)(0x80) /* FIFO Operating Mode Selection Bit 1 */
#define FXAS_F_SETUP_F_MODE_0                   (uint8_t)(0x00) /* 00: FIFO disabled mode */
#define FXAS_F_SETUP_F_MODE_1                   (uint8_t)(0x40) /* 01: Circular buffer mode */
#define FXAS_F_SETUP_F_MODE_2                   (uint8_t)(0x80) /* 1x: Stop mode */

/* FXAS_F_EVENT Bits */

#define FXAS_F_EVENT_FE_TIME0                    (uint8_t)(0x01) /* ODR periods elapsed since F_EVENT Set Bit 0 */
#define FXAS_F_EVENT_FE_TIME1                    (uint8_t)(0x02) /* ODR periods elapsed since F_EVENT Set Bit 1 */
#define FXAS_F_EVENT_FE_TIME2                    (uint8_t)(0x04) /* ODR periods elapsed since F_EVENT Set Bit 2 */
#define FXAS_F_EVENT_FE_TIME3                    (uint8_t)(0x08) /* ODR periods elapsed since F_EVENT Set Bit 3 */
#define FXAS_F_EVENT_FE_TIME4                    (uint8_t)(0x10) /* ODR periods elapsed since F_EVENT Set Bit 4 */
#define FXAS_F_EVENT_F_EVENT                     (uint8_t)(0x20) /* FIFO Event Flag, must read FIFO_STATUS to determine event. */

/* FXAS_INT_SRC_FLAG Bits */

#define FXAS_INT_SRC_FLAG_DRDY                   (uint8_t)(0x01) /* Data ready event source flag */
#define FXAS_INT_SRC_FLAG_RT                     (uint8_t)(0x02) /* Rate threshold event source flag */
#define FXAS_INT_SRC_FLAG_FIFO                   (uint8_t)(0x04) /* FIFO event source flag */
#define FXAS_INT_SRC_FLAG_BOOTEND                (uint8_t)(0x08) /* Boot sequence complete event source flag */

/* FXAS_CTRL_REG0 Bits */

#define FXAS_CTRL_REG0_FS0                       (uint8_t)(0x01) /* Full-scale Range Selection Bit 0 */
#define FXAS_CTRL_REG0_FS1                       (uint8_t)(0x02) /* Full-scale Range Selection Bit 1 */
#define FXAS_CTRL_REG0_FS_0                      (uint8_t)(0x00) /* FSR 2000dps, 62.5mdps/LSB */
#define FXAS_CTRL_REG0_FS_1                      (uint8_t)(0x01) /* FSR 1000dps, 31.25mdps/LSB */
#define FXAS_CTRL_REG0_FS_2                      (uint8_t)(0x02) /* FSR 500dps, 15.625mdps/LSB */
#define FXAS_CTRL_REG0_FS_3                      (uint8_t)(0x03) /* FSR 250dps, 7.8125mdps/LSB */
#define FXAS_CTRL_REG0_HPF_EN                    (uint8_t)(0x04) /* High-pass filter enable Bit */
#define FXAS_CTRL_REG0_SEL0                      (uint8_t)(0x08) /* HPF cutoff frequency selection Bit 0, table in datasheet */
#define FXAS_CTRL_REG0_SEL1                      (uint8_t)(0x10) /* HPF cutoff frequency selection Bit 1, table in datasheet */
#define FXAS_CTRL_REG0_SPIW                      (uint8_t)(0x20) /* SPI Interface mode selection */
#define FXAS_CTRL_REG0_BW0                       (uint8_t)(0x40) /* Low Pass filter cutoff frequency selection Bit 0, table in datasheet */
#define FXAS_CTRL_REG0_BW1                       (uint8_t)(0x80) /* Low Pass filter cutoff frequency selection Bit 1, table in datasheet */

/* FXAS_RT_CFG Bits */

#define FXAS_RT_CFG_XTEFE                        (uint8_t)(0x01) /* X-axis Rate Threshold Event Flag Enable Bit */
#define FXAS_RT_CFG_YTEFE                        (uint8_t)(0x02) /* Y-axis Rate Threshold Event Flag Enable Bit */
#define FXAS_RT_CFG_ZTEFE                        (uint8_t)(0x04) /* Z-axis Rate Threshold Event Flag Enable Bit */
#define FXAS_RT_CFG_ELE                          (uint8_t)(0x08) /* Event Latch Enable Bit */

/* FXAS_RT_SRC Bits */

#define FXAS_RT_SRC_X_RT_POL                     (uint8_t)(0x01) /* X-axis Rate Threshold Event Polarity (0: Positive, 1: Negative) */
#define FXAS_RT_SRC_XRT                          (uint8_t)(0x02) /* X-axis Rate Threshold Event Detected Bit */
#define FXAS_RT_SRC_Y_RT_POL                     (uint8_t)(0x04) /* Y-axis Rate Threshold Event Polarity (0: Positive, 1: Negative) */
#define FXAS_RT_SRC_YRT                          (uint8_t)(0x08) /* Y-axis Rate Threshold Event Detected Bit */
#define FXAS_RT_SRC_Z_RT_POL                     (uint8_t)(0x10) /* Z-axis Rate Threshold Event Polarity (0: Positive, 1: Negative) */
#define FXAS_RT_SRC_ZRT                          (uint8_t)(0x20) /* Z-axis Rate Threshold Event Detected Bit */
#define FXAS_RT_SRC_EA                           (uint8_t)(0x40) /* Event Active Flag (XRT, YRT, or ZRT have been asserted when active) */

/* FXAS_RT_THS Bits */

#define FXAS_RT_THS_THS0                         (uint8_t)(0x01) /* Unsigned 7-bit Rate Threshold value Bit 0 */
#define FXAS_RT_THS_THS1                         (uint8_t)(0x02) /* Unsigned 7-bit Rate Threshold value Bit 1 */
#define FXAS_RT_THS_THS2                         (uint8_t)(0x04) /* Unsigned 7-bit Rate Threshold value Bit 2 */
#define FXAS_RT_THS_THS3                         (uint8_t)(0x08) /* Unsigned 7-bit Rate Threshold value Bit 3 */
#define FXAS_RT_THS_THS4                         (uint8_t)(0x10) /* Unsigned 7-bit Rate Threshold value Bit 4 */
#define FXAS_RT_THS_THS5                         (uint8_t)(0x20) /* Unsigned 7-bit Rate Threshold value Bit 5 */
#define FXAS_RT_THS_THS6                         (uint8_t)(0x40) /* Unsigned 7-bit Rate Threshold value Bit 6 */
#define FXAS_RT_THX_DBCNTM                       (uint8_t)(0x80) /* Debounce Counter Mode Selection */

/* FXAS_CTRL_REG1 Bits */

#define FXAS_CTRL_REG1_STANDBY                   (uint8_t)(0x00) /* Standby Mode Selection */
#define FXAS_CTRL_REG1_READY                     (uint8_t)(0x01) /* Standby/Ready Mode Selection Bit */
#define FXAS_CTRL_REG1_ACTIVE                    (uint8_t)(0x02) /* Standby/Active Mode Selection Bit */
#define FXAS_CTRL_REG1_DR0                       (uint8_t)(0x04) /* Output Data Rate Selection Bit 0, table in datasheet */
#define FXAS_CTRL_REG1_DR1                       (uint8_t)(0x08) /* Output Data Rate Selection Bit 1, table in datasheet */
#define FXAS_CTRL_REG1_DR2                       (uint8_t)(0x10) /* Output Data Rate Selection Bit 2, table in datasheet */
#define FXAS_CTRL_REG1_DR_0                     (uint8_t)(0x00) /* ODR = 800Hz */
#define FXAS_CTRL_REG1_DR_1                     (uint8_t)(0x04) /* ODR = 400Hz */
#define FXAS_CTRL_REG1_DR_2                     (uint8_t)(0x08) /* ODR = 200Hz */
#define FXAS_CTRL_REG1_DR_3                     (uint8_t)(0x0C) /* ODR = 100Hz */
#define FXAS_CTRL_REG1_DR_4                     (uint8_t)(0x10) /* ODR = 50Hz */
#define FXAS_CTRL_REG1_DR_5                     (uint8_t)(0x14) /* ODR = 25Hz */
#define FXAS_CTRL_REG1_DR_6                     (uint8_t)(0x1C) /* ODR = 12.5Hz */

#define FXAS_CTRL_REG1_ST                        (uint8_t)(0x20) /* Self-test Enable Bit */
#define FXAS_CTRL_REG1_RST                       (uint8_t)(0x40) /* Device Reset Trigger Bit, self-cleared after assertion */

/* FXAS_CTRL_REG2 Bits */

#define FXAS_CTRL_REG2_PP_OD                     (uint8_t)(0x01) /* INT1 and INT2 pin output driver configuration */
#define FXAS_CTRL_REG2_IPOL                      (uint8_t)(0x02) /* Interrupt Logic Polarity Bit (Set for Active High Polarity) */
#define FXAS_CTRL_REG2_INT_EN_DRDY               (uint8_t)(0x04) /* Data ready interrupt enable */
#define FXAS_CTRL_REG2_INT_CFG_DRDY              (uint8_t)(0x08) /* Data ready interrupt pin routing */
#define FXAS_CTRL_REG2_INT_EN_RT                 (uint8_t)(0x10) /* Rate threshold interrupt enable */
#define FXAS_CTRL_REG2_INT_CFG_RT                (uint8_t)(0x20) /* Rate threshold interrupt pin routing */
#define FXAS_CTRL_REG2_INT_EN_FIFO               (uint8_t)(0x40) /* FIFO interrupt Enable */
#define FXAS_CTRL_REG2_INT_CFG_FIFO              (uint8_t)(0x80) /* FIFO interrupt pin routing */

/* FXAS_CTRL_REG3 Bits */

#define FXAS_CTRL_REG3_FS_DOUBLE                 (uint8_t)(0x01) /* Full-scale Range Expansion Enable (Doubles dynamic range of reading) */
#define FXAS_CTRL_REG3_EXTCTRLEN                 (uint8_t)(0x04) /* External Power Mode Control Input Bit*/
#define FXAS_CTRL_REG3_WRAPTOONE                 (uint8_t)(0x08) /* Auto-increment Address Read Pointer Bit */



#endif /* FXAS21002_H_ */
