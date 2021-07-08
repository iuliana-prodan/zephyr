/*
 * Copyright (c) 2021 NXP
 *
 * SPDX-License-Identifier: Apache-2.0
 */
/*
 * THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT.
 *
 * Functions here are designed to produce efficient code to
 * search an Xtensa bitmask of interrupts, inspecting only those bits
 * declared to be associated with a given interrupt level.  Each
 * dispatcher will handle exactly one flagged interrupt, in numerical
 * order (low bits first) and will return a mask of that bit that can
 * then be cleared by the calling code.  Unrecognized bits for the
 * level will invoke an error handler.
 */

#include <xtensa/config/core-isa.h>
#include <sys/util.h>
#include <sw_isr_table.h>

#if !defined(XCHAL_INT0_LEVEL) || XCHAL_INT0_LEVEL != 5
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT1_LEVEL) || XCHAL_INT1_LEVEL != 3
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT2_LEVEL) || XCHAL_INT2_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT3_LEVEL) || XCHAL_INT3_LEVEL != 3
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT4_LEVEL) || XCHAL_INT4_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT5_LEVEL) || XCHAL_INT5_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT6_LEVEL) || XCHAL_INT6_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT7_LEVEL) || XCHAL_INT7_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT8_LEVEL) || XCHAL_INT8_LEVEL != 1
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT9_LEVEL) || XCHAL_INT9_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT10_LEVEL) || XCHAL_INT10_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT11_LEVEL) || XCHAL_INT11_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT12_LEVEL) || XCHAL_INT12_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT13_LEVEL) || XCHAL_INT13_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT14_LEVEL) || XCHAL_INT14_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT15_LEVEL) || XCHAL_INT15_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT16_LEVEL) || XCHAL_INT16_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT17_LEVEL) || XCHAL_INT17_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT18_LEVEL) || XCHAL_INT18_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT19_LEVEL) || XCHAL_INT19_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif
#if !defined(XCHAL_INT20_LEVEL) || XCHAL_INT20_LEVEL != 2
#error core-isa.h interrupt level does not match dispatcher!
#endif

void set_sof_status(uint32_t status);
void my_cache_flush(void *addr, size_t bytes);
void set_status(uint32_t status, int idx);
void set_status_inc(int idx);

uint32_t my_int_mask_3[150];
uint32_t my_int_mask_3_cnt = 0;

uint32_t my_int_mask_3_cnt_logger_enabled = 0;
uint32_t my_int_mask_3_cnt_work_q_enabled = 0;

uint32_t my_int_mask_3_cnt_logger_started = 0;
uint32_t my_int_mask_3_cnt_work_q_started = 0;

uint32_t logger_enabled_mask_3_cnt_is;
uint32_t work_q_enabled_mask_3_cnt_is;

uint32_t logger_started_mask_3_cnt_is;
uint32_t work_q_started_mask_3_cnt_is;

extern uint32_t logger_enabled;
extern uint32_t work_q_enabled;

extern uint32_t logger_started;
extern uint32_t work_q_started;

extern uint32_t sof_status1[3];
extern uint32_t sof_status2[3];
extern uint32_t sof_status3[3];

uint32_t my_int_mask_1[100];
uint32_t my_int_mask_1_cnt = 0;

uint32_t my_int_mask_2[100];
uint32_t my_int_mask_2_cnt = 0;

uint32_t my_int_mask_5[100];
uint32_t my_int_mask_5_cnt = 0;

static inline int _xtensa_handle_one_int1(unsigned int mask)
{
	int irq;

	if (my_int_mask_1_cnt < 100)
		my_int_mask_1[my_int_mask_1_cnt] = mask;

	my_int_mask_1_cnt++;

	if (mask & BIT(8)) {
		mask = BIT(8);
		irq = 8;
		goto handle_irq;
	}
	return 0;
handle_irq:
	_sw_isr_table[irq].isr(_sw_isr_table[irq].arg);
	return mask;
}

static inline int _xtensa_handle_one_int2(unsigned int mask)
{
	int irq;
	int i = 0;

	if (my_int_mask_2_cnt < 100)
		my_int_mask_2[my_int_mask_2_cnt] = mask;

	my_int_mask_2_cnt++;

	set_status_inc(36);

	mask &= XCHAL_INTLEVEL2_MASK;
	for (i = 0; i <= 31; i++)
		if (mask & BIT(i)) {
			mask = BIT(i);
			irq = i;
			set_status_inc(37);
			goto handle_irq;
		}
	set_status_inc(38);
	return 0;
handle_irq:
	//set_status_inc(39);
	_sw_isr_table[irq].isr(_sw_isr_table[irq].arg);
	//set_status_inc(40);
	return mask;
}

static inline int _xtensa_handle_one_int3(unsigned int mask)
{
	int irq;

	if (my_int_mask_3_cnt < 150)
		my_int_mask_3[my_int_mask_3_cnt] = mask;

	my_int_mask_3_cnt++;

	//set_status_inc(32);

	if (logger_enabled) {
		my_int_mask_3_cnt_logger_enabled++;
		if (my_int_mask_3_cnt_logger_enabled == 1)
			// save and display my_int_mask_3_cnt
			logger_enabled_mask_3_cnt_is = my_int_mask_3_cnt;
	}

	if (logger_started) {
		my_int_mask_3_cnt_logger_started++;
		if (my_int_mask_3_cnt_logger_started == 1)
			// save and display my_int_mask_3_cnt
			logger_started_mask_3_cnt_is = my_int_mask_3_cnt;
	}

	if (work_q_enabled) {
		my_int_mask_3_cnt_work_q_enabled++;
		if (my_int_mask_3_cnt_work_q_enabled == 1)
			// save and display my_int_mask_3_cnt
			work_q_enabled_mask_3_cnt_is = my_int_mask_3_cnt;
	}

	if (work_q_started) {
		my_int_mask_3_cnt_work_q_started++;
		if (my_int_mask_3_cnt_work_q_started == 1)
			// save and display my_int_mask_3_cnt
			work_q_started_mask_3_cnt_is = my_int_mask_3_cnt;
	}

	if (mask & BIT(1)) {
		mask = BIT(1);
		irq = 1;
		//set_status_inc(33);
		goto handle_irq;
	}
	if (mask & BIT(3)) {
		mask = BIT(3);
		irq = 3;
		//set_status_inc(34);
		goto handle_irq;
	}
	if (mask & BIT(31)) {
		mask = BIT(31);
		irq = 31;
		//set_status_inc(35);
		goto handle_irq;
	}
	//set_status_inc(36);
	return 0;
handle_irq:
	//set_status_inc(37);
	_sw_isr_table[irq].isr(_sw_isr_table[irq].arg);
	//set_status_inc(49);
	return mask;
}

static inline int _xtensa_handle_one_int5(unsigned int mask)
{
	int irq;

	if (my_int_mask_5_cnt < 100)
		my_int_mask_5[my_int_mask_5_cnt] = mask;

	my_int_mask_5_cnt++;

	if (mask & BIT(0)) {
		mask = BIT(0);
		irq = 0;
		goto handle_irq;
	}
	return 0;
handle_irq:
	_sw_isr_table[irq].isr(_sw_isr_table[irq].arg);
	return mask;
}

static inline int _xtensa_handle_one_int0(unsigned int mask)
{
	return 0;
}

static inline int _xtensa_handle_one_int4(unsigned int mask)
{
	return 0;
}

static inline int _xtensa_handle_one_int6(unsigned int mask)
{
	return 0;
}

static inline int _xtensa_handle_one_int7(unsigned int mask)
{
	return 0;
}
