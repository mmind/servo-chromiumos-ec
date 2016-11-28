/* Copyright 2016 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* Snappy board configuration */

#ifndef __CROS_EC_BOARD_H
#define __CROS_EC_BOARD_H

/*
 * Allow dangerous commands.
 * TODO: Remove this config before production.
 */
#define CONFIG_SYSTEM_UNLOCKED

/*
 * By default, enable all console messages excepted HC, ACPI and event:
 * The sensor stack is generating a lot of activity.
 */
#define CC_DEFAULT     (CC_ALL & ~(CC_MASK(CC_EVENTS) | CC_MASK(CC_LPC)))
#undef CONFIG_HOSTCMD_DEBUG_MODE
#define CONFIG_HOSTCMD_DEBUG_MODE HCDEBUG_OFF


/* EC console commands  */
#define CONFIG_CMD_ACCELS
#define CONFIG_CMD_ACCEL_INFO
#define CONFIG_CMD_CHARGER_ADC_AMON_BMON
#define CONFIG_CHARGER_SENSE_RESISTOR		10
#define CONFIG_CHARGER_SENSE_RESISTOR_AC	10
#define BD9995X_IOUT_GAIN_SELECT \
		BD9995X_CMD_PMON_IOUT_CTRL_SET_IOUT_GAIN_SET_20V

#define CONFIG_CMD_CHARGER_PSYS
#define BD9995X_PSYS_GAIN_SELECT \
		BD9995X_CMD_PMON_IOUT_CTRL_SET_PMON_GAIN_SET_02UAW

#define CONFIG_CMD_I2C_STRESS_TEST
#define CONFIG_CMD_I2C_STRESS_TEST_ACCEL
#define CONFIG_CMD_I2C_STRESS_TEST_ALS
#define CONFIG_CMD_I2C_STRESS_TEST_BATTERY
#define CONFIG_CMD_I2C_STRESS_TEST_CHARGER
#define CONFIG_CMD_I2C_STRESS_TEST_TCPC

/* Battery */
#define CONFIG_BATTERY_DEVICE_CHEMISTRY  "LION"
#define CONFIG_BATTERY_CUT_OFF
#define CONFIG_BATTERY_PRESENT_CUSTOM
#define CONFIG_BATTERY_REVIVE_DISCONNECT
#define CONFIG_BATTERY_SMART

/* Charger */
#define CONFIG_CHARGE_MANAGER
#define CONFIG_CHARGE_RAMP
#define CONFIG_CHARGER
#define CONFIG_CHARGER_V2
#define CONFIG_CHARGER_BD99956
#define CONFIG_CHARGER_BD9995X_CHGEN
#define CONFIG_CHARGER_DISCHARGE_ON_AC
#define CONFIG_CHARGER_INPUT_CURRENT 512
#define CONFIG_CHARGER_LIMIT_POWER_THRESH_BAT_PCT 1
#define CONFIG_CHARGER_LIMIT_POWER_THRESH_CHG_MW 15000
#define CONFIG_CHARGER_MIN_BAT_PCT_FOR_POWER_ON 1
#define CONFIG_USB_CHARGER
#define CONFIG_CHARGE_MANAGER_EXTERNAL_POWER_LIMIT

/* USB-A config */
#define CONFIG_USB_PORT_POWER_SMART
#define CONFIG_USB_PORT_POWER_SMART_DEFAULT_MODE USB_CHARGE_MODE_CDP
#define CONFIG_USB_PORT_POWER_SMART_SIMPLE
#undef CONFIG_USB_PORT_POWER_SMART_PORT_COUNT
#define CONFIG_USB_PORT_POWER_SMART_PORT_COUNT 1
#define GPIO_USB_ILIM_SEL GPIO_USB_A_CHARGE_EN_L
#define GPIO_USB_CTL1 GPIO_EN_PP5000

/* USB PD config */
#define CONFIG_CASE_CLOSED_DEBUG_EXTERNAL
#define CONFIG_CMD_PD_CONTROL
#define CONFIG_USB_PD_ALT_MODE
#define CONFIG_USB_PD_ALT_MODE_DFP
#define CONFIG_USB_PD_CUSTOM_VDM
#define CONFIG_USB_PD_DUAL_ROLE
#define CONFIG_USB_PD_DUAL_ROLE_AUTO_TOGGLE
#define CONFIG_USB_PD_DISCHARGE
#define CONFIG_USB_PD_DISCHARGE_TCPC
#define CONFIG_USB_PD_LOGGING
#define CONFIG_USB_PD_LOG_SIZE 512
#define CONFIG_USB_PD_MAX_SINGLE_SOURCE_CURRENT TYPEC_RP_3A0
#define CONFIG_USB_PD_PORT_COUNT 2
#define CONFIG_USB_PD_QUIRK_SLOW_CC_STATUS
#define CONFIG_USB_PD_VBUS_DETECT_CHARGER
#define CONFIG_USB_PD_TCPC_LOW_POWER
#define CONFIG_USB_PD_TCPC_FW_VERSION
#define CONFIG_USB_PD_TCPM_MUX  /* for both PS8751 and ANX3429 */
#define CONFIG_USB_PD_TCPM_ANX74XX
#define CONFIG_USB_PD_TCPM_PS8751
#define CONFIG_USB_PD_TCPM_TCPCI
#define CONFIG_USB_PD_TRY_SRC
#define CONFIG_USB_POWER_DELIVERY

#define CONFIG_USBC_SS_MUX
#define CONFIG_USBC_SS_MUX_DFP_ONLY
#define CONFIG_USBC_VCONN
#define CONFIG_USBC_VCONN_SWAP

/* SoC / PCH */
#define CONFIG_LPC
#define CONFIG_CHIPSET_APOLLOLAKE
#define CONFIG_CHIPSET_RESET_HOOK
#undef CONFIG_PECI
#define CONFIG_POWER_BUTTON
#define CONFIG_POWER_BUTTON_X86
#define CONFIG_POWER_COMMON

/* EC */
#define CONFIG_ADC
#define CONFIG_BOARD_VERSION
#define CONFIG_BOARD_SPECIFIC_VERSION
#define CONFIG_BUTTON_COUNT 2
#define CONFIG_EXTPOWER_GPIO
#undef   CONFIG_EXTPOWER_DEBOUNCE_MS
#define  CONFIG_EXTPOWER_DEBOUNCE_MS 1000
#define CONFIG_FPU
#define CONFIG_HOSTCMD_FLASH_SPI_INFO
#define CONFIG_I2C
#define CONFIG_I2C_MASTER
#define CONFIG_KEYBOARD_PROTOCOL_8042
#define CONFIG_KEYBOARD_COL2_INVERTED
#define CONFIG_KEYBOARD_FACTORY_TEST
#define CONFIG_KEYBOARD_PWRBTN_ASSERTS_KSI2
#define CONFIG_LED_COMMON
#define CONFIG_LID_SWITCH
#define CONFIG_LOW_POWER_IDLE
#define CONFIG_LTO
#define CONFIG_POWER_SIGNAL_INTERRUPT_STORM_DETECT_THRESHOLD 30
#define CONFIG_PWM
#define CONFIG_TEMP_SENSOR
#define CONFIG_THERMISTOR_NCP15WB
#define CONFIG_DPTF
#define CONFIG_SCI_GPIO GPIO_PCH_SCI_L
#define CONFIG_UART_HOST 0
#define CONFIG_VBOOT_HASH
#define CONFIG_BACKLIGHT_LID
#define CONFIG_WIRELESS
#define CONFIG_WIRELESS_SUSPEND EC_WIRELESS_SWITCH_WLAN_POWER
#define CONFIG_WLAN_POWER_ACTIVE_LOW
#define  WIRELESS_GPIO_WLAN_POWER GPIO_WIRELESS_GPIO_WLAN_POWER

#define CONFIG_FLASH_SIZE 524288
#define CONFIG_SPI_FLASH_W25Q40	/* FIXME: Should be GD25LQ40? */

/*
 * Enable 1 slot of secure temporary storage to support
 * suspend/resume with read/write memory training.
 */
#define CONFIG_VSTORE
#define CONFIG_VSTORE_SLOT_COUNT 1

/* Optional feature - used by nuvoton */
#define NPCX_UART_MODULE2    1 /* 0:GPIO10/11 1:GPIO64/65 as UART */
#define NPCX_JTAG_MODULE2    0 /* 0:GPIO21/17/16/20 1:GPIOD5/E2/D4/E5 as JTAG*/
/*
 * FIXME(dhendrix): these pins are just normal GPIOs on Snappy. Do we need
 * to change some other setting to put them in GPIO mode?
 */
#define NPCX_TACH_SEL2       0 /* 0:GPIO40/A4 1:GPIO93/D3 as TACH */

/* I2C ports */
#define I2C_PORT_GYRO			NPCX_I2C_PORT1
#define I2C_PORT_LID_ACCEL		NPCX_I2C_PORT2
#define I2C_PORT_ALS			NPCX_I2C_PORT2
#define I2C_PORT_BARO			NPCX_I2C_PORT2
#define I2C_PORT_BATTERY		NPCX_I2C_PORT3
#define I2C_PORT_CHARGER		NPCX_I2C_PORT3
/* Accelerometer and Gyroscope are the same device. */
#define I2C_PORT_ACCEL			I2C_PORT_GYRO

/* Sensors */
#define CONFIG_MKBP_EVENT
#define CONFIG_MKBP_USE_HOST_EVENT
#define CONFIG_ACCELGYRO_BMI160
#define CONFIG_ACCEL_INTERRUPTS
#define CONFIG_ACCELGYRO_BMI160_INT_EVENT TASK_EVENT_CUSTOM(4)
#define CONFIG_MAG_BMI160_BMM150
#define BMM150_I2C_ADDRESS BMM150_ADDR0	/* 8-bit address */
#define CONFIG_MAG_CALIBRATE
#define CONFIG_ACCEL_KX022
#define CONFIG_ALS
#define CONFIG_ALS_OPT3001
#define OPT3001_I2C_ADDR OPT3001_I2C_ADDR1
#define CONFIG_BARO_BMP280
#define CONFIG_LID_ANGLE
#define CONFIG_LID_ANGLE_SENSOR_BASE BASE_ACCEL
#define CONFIG_LID_ANGLE_SENSOR_LID LID_ACCEL

/* FIFO size is in power of 2. */
#define CONFIG_ACCEL_FIFO 1024

/* Depends on how fast the AP boots and typical ODRs */
#define CONFIG_ACCEL_FIFO_THRES (CONFIG_ACCEL_FIFO / 3)


#ifndef __ASSEMBLER__

#include "gpio_signal.h"
#include "registers.h"

/* ADC signal */
enum adc_channel {
	ADC_TEMP_SENSOR_CHARGER,	/* ADC0 */
	ADC_TEMP_SENSOR_AMB,		/* ADC1 */
	ADC_BOARD_ID,			/* ADC2 */
	ADC_CH_COUNT
};

enum pwm_channel {
	/* Number of PWM channels */
	PWM_CH_COUNT
};

enum power_signal {
	X86_RSMRST_N = 0,
	X86_SLP_S0_N,
	X86_SLP_S3_N,
	X86_SLP_S4_N,
	X86_SUSPWRDNACK,

	X86_ALL_SYS_PG,		/* PMIC_EC_PWROK_OD */
	X86_PGOOD_PP3300,	/* GPIO_PP3300_PG */
	X86_PGOOD_PP5000,	/* GPIO_PP5000_PG */

	/* Number of X86 signals */
	POWER_SIGNAL_COUNT
};

enum temp_sensor_id {
	TEMP_SENSOR_BATTERY = 0,
	TEMP_SENSOR_AMBIENT,
	TEMP_SENSOR_CHARGER,
	TEMP_SENSOR_COUNT
};

/* Light sensors */
enum als_id {
	ALS_OPT3001 = 0,

	ALS_COUNT
};

/*
 * Motion sensors:
 * When reading through IO memory is set up for sensors (LPC is used),
 * the first 2 entries must be accelerometers, then gyroscope.
 * For BMI160, accel, gyro and compass sensors must be next to each other.
 */
enum sensor_id {
	LID_ACCEL = 0,
	BASE_ACCEL,
	BASE_GYRO,
	BASE_MAG,
	BASE_BARO,
};

enum snappy_board_version {
	BOARD_VERSION_UNKNOWN = -1,
	BOARD_VERSION_1,
	BOARD_VERSION_2,
	BOARD_VERSION_3,
	BOARD_VERSION_4,
	BOARD_VERSION_5,
	BOARD_VERSION_6,
	BOARD_VERSION_7,
	BOARD_VERSION_8,
	BOARD_VERSION_COUNT,
};

/* start as a sink in case we have no other power supply/battery */
#define PD_DEFAULT_STATE PD_STATE_SNK_DISCONNECTED

/* TODO: determine the following board specific type-C power constants */
/* FIXME(dhendrix): verify all of the below PD_* numbers */
/*
 * delay to turn on the power supply max is ~16ms.
 * delay to turn off the power supply max is about ~180ms.
 */
#define PD_POWER_SUPPLY_TURN_ON_DELAY  30000  /* us */
#define PD_POWER_SUPPLY_TURN_OFF_DELAY 250000 /* us */

/* delay to turn on/off vconn */
#define PD_VCONN_SWAP_DELAY 5000 /* us */

/* Define typical operating power and max power */
#define PD_OPERATING_POWER_MW 15000
#define PD_MAX_POWER_MW       45000
#define PD_MAX_CURRENT_MA     3000
#define PD_MAX_VOLTAGE_MV     20000

#ifdef CONFIG_KEYBOARD_FACTORY_TEST
extern const int keyboard_factory_scan_pins[][2];
extern const int keyboard_factory_scan_pins_used;
#endif

/* Reset PD MCU */
void board_reset_pd_mcu(void);

int board_get_version(void);

void board_set_tcpc_power_mode(int port, int mode);
void board_print_tcpc_fw_version(int port);

/* Sensors without hardware FIFO are in forced mode */
#define CONFIG_ACCEL_FORCE_MODE_MASK \
	((1 << LID_ACCEL) | (1 << BASE_BARO))

#endif /* !__ASSEMBLER__ */

#endif /* __CROS_EC_BOARD_H */
