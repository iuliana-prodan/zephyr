/*
 * Copyright 2025 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/misc/addr_translation/addr_translation.h>

#define DT_DRV_COMPAT zephyr_addr_translation

#define LOG_MODULE_NAME addr_translation
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

/* No more than 1 instance should be used */
#if DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) > 1
#error "Only one node with zephyr_addr_translation compatible should be used"
#endif

/* Node has to have the dma-ranges property */
#if DT_NODE_HAS_PROP(DT_DRV_INST(0), dma-ranges)
#error "The node with zephyr_addr_translation compatible should have dma-ranges property"
#endif

/*
 * Fills the ranges table from DT
 */
#define ADDR_TRANSLATION_DMA_RANGE_FORMAT(node_id, idx)				\
{										\
	.device_addr = DT_DMA_RANGES_CHILD_BUS_ADDRESS_BY_IDX(node_id, idx),	\
	.driver_addr = DT_DMA_RANGES_PARENT_BUS_ADDRESS_BY_IDX(node_id, idx),	\
	.map_length = DT_DMA_RANGES_LENGTH_BY_IDX(node_id, idx),		\
}										\

/** @brief Structure describing a device that supports the PCI Express Controller API
 */
struct addr_xlate {
	/* device offset from the start of the region */
	metal_phys_addr_t device_addr;
	/* driver offset from the start of the region */
	metal_phys_addr_t driver_addr;
	/* region size */
	size_t map_length;
};

/* Array of drv physical address of each of the pages in the I/O region */
struct addr_xlate map[] = {DT_FOREACH_DMA_RANGE(DT_DRV_INST(0), ADDR_TRANSLATION_DMA_RANGE_FORMAT)};


#define RANGE_LENGTH(node_id, idx) DT_DMA_RANGES_LENGTH_BY_IDX(node_id, idx),
size_t ranges_length[] = {DT_FOREACH_DMA_RANGE(DT_NODELABEL(addr_trans), RANGE_LENGTH)};

#define PARENT_ADDR(node_id, idx) DT_DMA_RANGES_PARENT_BUS_ADDRESS_BY_IDX(node_id, idx),
size_t parent_addr[] = {DT_FOREACH_DMA_RANGE(DT_NODELABEL(addr_trans), PARENT_ADDR)};

#define CHILD_ADDR(node_id, idx) DT_DMA_RANGES_CHILD_BUS_ADDRESS_BY_IDX(node_id, idx),
size_t child_addr[] = {DT_FOREACH_DMA_RANGE(DT_NODELABEL(addr_trans), CHILD_ADDR)};

static const metal_phys_addr_t physmap_driver = DT_DMA_RANGES_PARENT_BUS_ADDRESS_BY_IDX(DT_NODELABEL(addr_trans), 0);
static const metal_phys_addr_t physmap_device = DT_DMA_RANGES_CHILD_BUS_ADDRESS_BY_IDX(DT_NODELABEL(addr_trans), 0);

/*  ************************  */

#define TRANSLATION_REG_ADDRESS(idx, inst) DT_INST_REG_ADDR_BY_IDX(inst, idx)
/* Array of drv physical address of each of the pages in the I/O region */
static const metal_phys_addr_t physmap[] = {
	LISTIFY(DT_NUM_REGS(DT_DRV_INST(0)), TRANSLATION_REG_ADDRESS, (,), 0)
};

/*  ************************  */

static metal_phys_addr_t offset_to_phys_helper(struct metal_io_region *io,
					       unsigned long offset,
					       metal_phys_addr_t *phys)
{
	unsigned long page = (io->page_shift >= sizeof(offset) * CHAR_BIT ?
			     0 : offset >> io->page_shift);

	return (phys && offset < io->size
		? phys[page] + (offset & io->page_mask)
		: METAL_BAD_PHYS);
}
static metal_phys_addr_t translate_offset_to_phys(struct metal_io_region *io,
						  unsigned long offset)
{
	metal_phys_addr_t tmp_phys = offset_to_phys_helper(io, offset, &physmap_driver);

	if (tmp_phys != METAL_BAD_PHYS) {
		return tmp_phys;
	}

	return offset_to_phys_helper(io, offset, &physmap_device);
}

static unsigned long phys_to_offset_helper(struct metal_io_region *io,
					   metal_phys_addr_t phys,
					   metal_phys_addr_t *map)
{
	unsigned long offset =
		(io->page_mask == (metal_phys_addr_t)(-1) ?
		phys - map[0] :  phys & io->page_mask);
	do {
		if (offset_to_phys_helper(io, offset, map) == phys) {
			return offset;
		}
		offset += io->page_mask + 1;
	} while (offset < io->size);

	return METAL_BAD_OFFSET;
}

static unsigned long translate_phys_to_offset(struct metal_io_region *io,
					      metal_phys_addr_t phys)
{
	unsigned long tmp_offset = phys_to_offset_helper(io, phys, &physmap_driver);

	if (tmp_offset != METAL_BAD_OFFSET) {
		return tmp_offset;
	}

	return phys_to_offset_helper(io, phys, &physmap_device);
}

static const struct metal_io_ops openamp_addr_translation_ops = {
	.phys_to_offset = translate_phys_to_offset,
	.offset_to_phys = translate_offset_to_phys,
};

#define OPENAMP_ADDR_TRANSLATION_INIT(idx)                                    \
	DEVICE_DT_INST_DEFINE(idx, NULL,                                      \
			      NULL, NULL, NULL,                               \
			      POST_KERNEL,                                    \
			      CONFIG_KERNEL_INIT_PRIORITY_DEFAULT,            \
			      &openamp_addr_translation_ops,                  \
			      NULL);

DT_INST_FOREACH_STATUS_OKAY(OPENAMP_ADDR_TRANSLATION_INIT)

