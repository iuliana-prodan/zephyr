# Copyright 2024 NXP
# SPDX-License-Identifier: Apache-2.0

zephyr_include_directories(public)

set(LIB_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/lib)
add_library(natureDspLib STATIC IMPORTED GLOBAL)
set_target_properties(natureDspLib PROPERTIES IMPORTED_LOCATION ${LIB_DIR}/natureDspLib.a)
target_link_libraries(app PUBLIC natureDspLib)

zephyr_include_directories_ifdef(CONFIG_DSP_BACKEND_XTENSANDSP
  /opt/samba/nxa06898/xcc/imx-naturedsp/hifi4_library/include
)

zephyr_include_directories_ifdef(CONFIG_DSP_BACKEND_XTENSANDSP
  /opt/samba/nxa06898/xcc/imx-naturedsp/hifi4_library/include_private
)

