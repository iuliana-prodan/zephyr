#
# Copyright (c) 2020, STMicroelectronics
# Copyright 2025 NXP
#
# SPDX-License-Identifier: Apache-2.0
#

zephyr_include_directories_ifdef(CONFIG_OPENAMP_RSC_TABLE_PRESENT .)

if(CONFIG_OPENAMP_VENDOR_RSC_TABLE OR CONFIG_OPENAMP_ADDR_TRANSLATION)
  zephyr_include_directories(vendor)
endif()

# include vendor-specific resource table files
if(CONFIG_OPENAMP_VENDOR_RSC_TABLE)
  zephyr_sources(vendor/${CONFIG_OPENAMP_VENDOR_RSC_TABLE_FILE})
elseif(CONFIG_OPENAMP_RSC_TABLE)
# include generic resource table
  zephyr_sources(resource_table.c)
endif()

# include address translation files
zephyr_sources(addr_translation.c)
