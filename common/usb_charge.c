/* Copyright (c) 2012 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/* USB charging control module for Chrome EC */

#include "board.h"
#include "chipset.h"
#include "console.h"
#include "gpio.h"
#include "hooks.h"
#include "system.h"
#include "usb_charge.h"
#include "util.h"


#define USB_SYSJUMP_TAG 0x5550 /* "UP" - Usb Port */
#define USB_HOOK_VERSION 1
/* The previous USB port state before sys jump */
struct usb_state {
	uint8_t port_mode[USB_CHARGE_PORT_COUNT];
	uint8_t pad[2]; /* Pad to 4 bytes for system_add_jump_tag(). */
};


static uint8_t charge_mode[USB_CHARGE_PORT_COUNT];


static void usb_charge_set_control_mode(int port_id, int mode)
{
	if (port_id == 0) {
		gpio_set_level(GPIO_USB1_CTL1, (mode & 0x4) >> 2);
		gpio_set_level(GPIO_USB1_CTL2, (mode & 0x2) >> 1);
		gpio_set_level(GPIO_USB1_CTL3, mode & 0x1);
	}
	else if (port_id == 1) {
		gpio_set_level(GPIO_USB2_CTL1, (mode & 0x4) >> 2);
		gpio_set_level(GPIO_USB2_CTL2, (mode & 0x2) >> 1);
		gpio_set_level(GPIO_USB2_CTL3, mode & 0x1);
	}
}


static void usb_charge_set_enabled(int port_id, int en)
{
	if (port_id == 0)
		gpio_set_level(GPIO_USB1_ENABLE, en);
	else
		gpio_set_level(GPIO_USB2_ENABLE, en);
}


static void usb_charge_set_ilim(int port_id, int sel)
{
	if (port_id == 0)
		gpio_set_level(GPIO_USB1_ILIM_SEL, sel);
	else
		gpio_set_level(GPIO_USB2_ILIM_SEL, sel);
}


static int usb_charge_all_ports_on(void)
{
	usb_charge_set_mode(0, USB_CHARGE_MODE_DOWNSTREAM_500MA);
	usb_charge_set_mode(1, USB_CHARGE_MODE_DOWNSTREAM_500MA);
	return EC_SUCCESS;
}


static int usb_charge_all_ports_off(void)
{
	usb_charge_set_mode(0, USB_CHARGE_MODE_DISABLED);
	usb_charge_set_mode(1, USB_CHARGE_MODE_DISABLED);
	return EC_SUCCESS;
}


int usb_charge_set_mode(int port_id, enum usb_charge_mode mode)
{
	if (port_id >= USB_CHARGE_PORT_COUNT)
		return EC_ERROR_INVAL;

	if (mode == USB_CHARGE_MODE_DISABLED) {
		usb_charge_set_enabled(port_id, 0);
		return EC_SUCCESS;
	}
	else
		usb_charge_set_enabled(port_id, 1);

	switch (mode) {
		case USB_CHARGE_MODE_CHARGE_AUTO:
			usb_charge_set_control_mode(port_id, 1);
			usb_charge_set_ilim(port_id, 1);
			break;
		case USB_CHARGE_MODE_CHARGE_BC12:
			usb_charge_set_control_mode(port_id, 4);
			break;
		case USB_CHARGE_MODE_DOWNSTREAM_500MA:
			usb_charge_set_control_mode(port_id, 2);
			usb_charge_set_ilim(port_id, 0);
			break;
		case USB_CHARGE_MODE_DOWNSTREAM_1500MA:
			usb_charge_set_control_mode(port_id, 2);
			usb_charge_set_ilim(port_id, 1);
			break;
		default:
			return EC_ERROR_UNKNOWN;
	}

	charge_mode[port_id] = mode;

	return EC_SUCCESS;
}

/*****************************************************************************/
/* Console commands */

static int command_set_mode(int argc, char **argv)
{
	int port_id = -1;
	int mode = -1;
	char *e;

	if (argc != 3)
		return EC_ERROR_PARAM_COUNT;

	port_id = strtoi(argv[1], &e, 0);
	if (*e || port_id < 0 || port_id >= USB_CHARGE_PORT_COUNT)
		return EC_ERROR_PARAM1;

	mode = strtoi(argv[2], &e, 0);
	if (*e || mode < 0 || mode >= USB_CHARGE_MODE_COUNT)
		return EC_ERROR_PARAM2;

	return usb_charge_set_mode(port_id, mode);
}
DECLARE_CONSOLE_COMMAND(usbchargemode, command_set_mode,
			"<port> <0 | 1 | 2 | 3 | 4>",
			"Set USB charge mode",
			"Modes: 0=Disabled.\n"
			"       1=Dedicated charging. Auto select.\n"
			"       2=Dedicated charging. BC 1.2.\n"
			"       3=Downstream. Max 500mA.\n"
			"       4=Downstream. Max 1.5A.\n");


/*****************************************************************************/
/* Hooks */

static int usb_charge_preserve_state(void)
{
	struct usb_state state;

	state.port_mode[0] = charge_mode[0];
	state.port_mode[1] = charge_mode[1];

	system_add_jump_tag(USB_SYSJUMP_TAG, USB_HOOK_VERSION,
			    sizeof(state), &state);
	return EC_SUCCESS;
}
DECLARE_HOOK(HOOK_SYSJUMP, usb_charge_preserve_state, HOOK_PRIO_DEFAULT);

static int usb_charge_init(void)
{
	const struct usb_state *prev;
	int version, size;

	prev = (const struct usb_state *)system_get_jump_tag(USB_SYSJUMP_TAG,
							     &version, &size);
	if (prev && version == USB_HOOK_VERSION && size == sizeof(*prev)) {
		usb_charge_set_mode(0, prev->port_mode[0]);
		usb_charge_set_mode(1, prev->port_mode[1]);
	}
	else
		usb_charge_all_ports_off();

	return EC_SUCCESS;
}
DECLARE_HOOK(HOOK_INIT, usb_charge_init, HOOK_PRIO_DEFAULT);


static int usb_charge_startup(void)
{
	/* Turn on USB ports on as we go into S3 or S0. */
	usb_charge_all_ports_on();
	return EC_SUCCESS;
}
DECLARE_HOOK(HOOK_CHIPSET_STARTUP, usb_charge_startup, HOOK_PRIO_DEFAULT);


static int usb_charge_shutdown(void)
{
	/* Turn on USB ports off as we go back to S5. */
	usb_charge_all_ports_off();
	return EC_SUCCESS;
}
DECLARE_HOOK(HOOK_CHIPSET_SHUTDOWN, usb_charge_shutdown, HOOK_PRIO_DEFAULT);
