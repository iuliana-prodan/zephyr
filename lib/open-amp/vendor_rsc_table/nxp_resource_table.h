/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define RESOURCE_TABLE_VENDOR_PAYLOAD						\
	.vendor_hdr = {								\
		.type = 128,							\
		.len = 16,							\
	},									\
	.vendor_payload = {							\
		0x6E787073,	/* FW_RSC_NXP_S_MAGIC, 'n''x''p''s' */	\
		0x00,		/* version */ 				\
		0x01		/* NOT wait for a FW_READY response */	\
	}
