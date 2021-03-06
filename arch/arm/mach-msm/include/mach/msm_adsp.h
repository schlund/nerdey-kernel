/* include/asm-arm/arch-msm/msm_adsp.h
 *
 * Copyright (C) 2008 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 */

#ifndef __ASM__ARCH_MSM_ADSP_H
#define __ASM__ARCH_MSM_ADSP_H

struct msm_adsp_module;

struct msm_adsp_ops {
	/* event is called from interrupt context when a message
	 * arrives from the DSP.  Use the provided function pointer
	 * to copy the message into a local buffer.  Do NOT call
	 * it multiple times.
	 */
	void (*event)(void *driver_data, unsigned id, size_t len,
		      void (*getevent)(void *ptr, size_t len));
	void (*modem_event) (void *driver_data, uint32_t image);
};

/* Get, Put, Enable, and Disable are synchronous and must only
 * be called from thread context.  Enable and Disable will block
 * up to one second in the event of a fatal DSP error but are
 * much faster otherwise.
 */
int msm_adsp_get(const char *name, struct msm_adsp_module **module,
		 struct msm_adsp_ops *ops, void *driver_data);
void msm_adsp_put(struct msm_adsp_module *module);
int msm_adsp_enable(struct msm_adsp_module *module);
int msm_adsp_disable(struct msm_adsp_module *module);
int adsp_set_clkrate(struct msm_adsp_module *module, unsigned long clk_rate);
int msm_adsp_disable_event_rsp(struct msm_adsp_module *module);

/* Write is safe to call from interrupt context.
 */
int msm_adsp_write(struct msm_adsp_module *module,
		   unsigned queue_id,
		   void *data, size_t len);

#define QDSP_mpuAfeQueue                  0
#define QDSP_mpuRmtQueue                  1
#define QDSP_mpuVDecCmdQueue              2
#define QDSP_mpuVDecPktQueue              3
#define QDSP_mpuVEncCmdQueue              4
#define QDSP_rxMpuDecCmdQueue             5
#define QDSP_rxMpuDecPktQueue             6
#define QDSP_txMpuEncQueue                7
#define QDSP_uPAudPPCmd1Queue             8
#define QDSP_uPAudPPCmd2Queue             9
#define QDSP_uPAudPPCmd3Queue             10
#define QDSP_uPAudPlay0BitStreamCtrlQueue 11
#define QDSP_uPAudPlay1BitStreamCtrlQueue 12
#define QDSP_uPAudPlay2BitStreamCtrlQueue 13
#define QDSP_uPAudPlay3BitStreamCtrlQueue 14
#define QDSP_uPAudPlay4BitStreamCtrlQueue 15
#define QDSP_uPAudPreProcCmdQueue         16
#define QDSP_uPAudRecBitStreamQueue       17
#define QDSP_uPAudRecCmdQueue             18
#define QDSP_uPDiagQueue                  19
#define QDSP_uPJpegFTMActionCmdQueue      20
#define QDSP_uPJpegFTMCfgCmdQueue         21
#define QDSP_uPJpegActionCmdQueue         22
#define QDSP_uPJpegCfgCmdQueue            23
#define QDSP_uPVocProcQueue               24
#define QDSP_vfeCommandQueue              25
#define QDSP_vfeCommandScaleQueue         26
#define QDSP_vfeCommandTableQueue         27
#define QDSP_vfeFTMCommandQueue           28
#define QDSP_vfeFTMCommandScaleQueue      29
#define QDSP_vfeFTMCommandTableQueue      30

#define QDSP_MAX_NUM_QUEUES               31

#endif
