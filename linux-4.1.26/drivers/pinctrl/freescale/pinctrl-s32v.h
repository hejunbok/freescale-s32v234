/*
 * S32V pinmux core definitions
 *
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 * Copyright (C) 2012 Linaro Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __DRIVERS_PINCTRL_S32V_H
#define __DRIVERS_PINCTRL_S32V_H

/**
 * Pinctrl driver versions
 */
enum s32v_pinctrl_version {
	/* Pinctrl driver reserves all SIUL2 registers */
	PINCTRL_V1,
	/* Pinctrl driver reserves only pinctrl registers */
	PINCTRL_V2,
};

struct platform_device;

/**
 * struct s32v_pin - describes a single S32V pin
 * @pin_id: the pin_id of this pin
 * @config: the config for this pin.
 */
struct s32v_pin {
	unsigned int pin_id;
	unsigned long config;
};

/**
 * struct s32v_pin_group - describes an S32V pin group
 * @name: the name of this specific pin group
 * @npins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 * @pin_ids: array of pin_ids. pinctrl forces us to maintain such an array
 * @pins: array of pins
 */
struct s32v_pin_group {
	const char *name;
	unsigned npins;
	unsigned int *pin_ids;
	struct s32v_pin *pins;
};

/**
 * struct s32v_pmx_func - describes S32V pinmux functions
 * @name: the name of this specific function
 * @groups: corresponding pin groups
 * @num_groups: the number of groups
 */
struct s32v_pmx_func {
	const char *name;
	const char **groups;
	unsigned num_groups;
};


struct s32v_pinctrl_soc_info {
	struct device *dev;
	const struct pinctrl_pin_desc *pins;
	unsigned int npins;
	struct s32v_pin_group *groups;
	unsigned int ngroups;
	struct s32v_pmx_func *functions;
	unsigned int nfunctions;
	unsigned int flags;
};

#define S32V_PINCTRL_PIN(pin)	PINCTRL_PIN(pin, #pin)
#define S32V_MSCR_OFFSET	(0x240)
#define S32V_PAD_CONFIG(idx)	((idx) * 4)
#define S32V_PIN_SIZE		(8)


int s32v_pinctrl_probe(struct platform_device *pdev,
			struct s32v_pinctrl_soc_info *info,
			enum s32v_pinctrl_version vers);
int s32v_pinctrl_remove(struct platform_device *pdev);
#endif /* __DRIVERS_PINCTRL_S32V_H */
