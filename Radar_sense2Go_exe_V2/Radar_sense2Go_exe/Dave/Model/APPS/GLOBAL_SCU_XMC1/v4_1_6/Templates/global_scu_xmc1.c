/**
 * @file global_scu_xmc1.c
 * @date 2015-10-09
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 */
/**
 * @cond
 ***********************************************************************************************************************
 * GLOBAL_SCU_XMC1 v4.1.6 - Registers the callback for SCU Interrupt
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2015-02-16:
 *     - Initial version<br>
 *
 * 2015-06-01:
 *     - GLOBAL_SCU_XMC4_CHECK_EVENT static inline API added
 *     - GLOBAL_SCU_XMC4_RegisterCallback API signature modified <br>
 * 2015-07-30:
 *     - Added new IRQ handlers for XMC14
 * 2015-10-09:
 *     - Added XMC_SCU_SetInterruptControl() before enabling IRQ for XMC14 
 * @endcond
 *
 */
/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/
#include "global_scu_xmc1.h"
/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/
#if defined(XMC_ASSERT_ENABLE)
#define GLOBAL_SCU_XMC1_CHECK_EVENT(event) ((event == GLOBAL_SCU_XMC1_EVENT_WDT_WARNING) || \
		                                    (event == GLOBAL_SCU_XMC1_EVENT_RTC_PERIODIC) || \
		                                    (event == GLOBAL_SCU_XMC1_EVENT_RTC_ALARM) || \
											(event == GLOBAL_SCU_XMC1_EVENT_LOSS_EXT_CLOCK) || \
											(event == GLOBAL_SCU_XMC1_EVENT_DCO1_OUT_SYNC))
#endif
/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/
#if (UC_SERIES != XMC14)
void SCU_0_IRQHandler(void);
void SCU_1_IRQHandler(void);
void SCU_2_IRQHandler(void);
#else
void IRQ0_Handler(void);
void IRQ1_Handler(void);
void IRQ2_Handler(void);
#endif
/**********************************************************************************************************************
* API IMPLEMENTATION
**********************************************************************************************************************/

/*
 * API to retrieve the version of the GLOBAL_SCU_XMC1 APP
 */
DAVE_APP_VERSION_t GLOBAL_SCU_XMC1_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;

  version.major = GLOBAL_SCU_XMC1_MAJOR_VERSION;
  version.minor = GLOBAL_SCU_XMC1_MINOR_VERSION;
  version.patch = GLOBAL_SCU_XMC1_PATCH_VERSION;

  return (version);
}

/*  Function to configure SCU Interrupts based on  user configuration.
 * 
 */
GLOBAL_SCU_XMC1_STATUS_t GLOBAL_SCU_XMC1_Init(GLOBAL_SCU_XMC1_t*const handle)
{
  GLOBAL_SCU_XMC1_STATUS_t initstatus;

  XMC_ASSERT("GLOBAL_SCU_XMC1_Init: NULL handle", (handle != NULL));

  if (handle->initialized == false)
  {
    NVIC_SetPriority((IRQn_Type)0U,(uint32_t)handle->config->priority[0]);
  	NVIC_SetPriority((IRQn_Type)1U,(uint32_t)handle->config->priority[1]);
  	NVIC_SetPriority((IRQn_Type)2U,(uint32_t)handle->config->priority[2]);

  	/* enable the IRQ0 */
  	if (handle->config->enable_at_init[0] == true)
  	{
#if (UC_SERIES == XMC14)
  	  XMC_SCU_SetInterruptControl(0, XMC_SCU_IRQCTRL_SCU_SR0_IRQ0);
#endif
  	  NVIC_EnableIRQ((IRQn_Type)0U);
  	}
  	/* enable the IRQ1 */
  	if (handle->config->enable_at_init[1] == true)
  	{
#if (UC_SERIES == XMC14)
  	  XMC_SCU_SetInterruptControl(1, XMC_SCU_IRQCTRL_SCU_SR1_IRQ1);
#endif
  	  NVIC_EnableIRQ((IRQn_Type)1U);
  	}
  	/* enable the IRQ2 */
  	if (handle->config->enable_at_init[2] == true)
  	{
#if (UC_SERIES == XMC14)
  	  XMC_SCU_SetInterruptControl(2, XMC_SCU_IRQCTRL_SCU_SR2_IRQ2);
#endif
      NVIC_EnableIRQ((IRQn_Type)2U);
  	}
	handle->initialized = true;
    initstatus = GLOBAL_SCU_XMC1_STATUS_SUCCESS;
  }
  else
  {
    initstatus = GLOBAL_SCU_XMC1_STATUS_FAILURE;
  }
  	
  return (initstatus);
}

#if (UC_SERIES != XMC14)
/*
 * @brief  SCU_0 Interrupt Handler
 */
void SCU_0_IRQHandler(void)
{
  XMC_SCU_IRQHandler(0U);
}

/*  SCU_1 Interrupt Handler.
 * 
 */
void SCU_1_IRQHandler(void)
{
  XMC_SCU_IRQHandler(1U);
}

/*  SCU2 Interrupt Handler.
 *
 */
void SCU_2_IRQHandler(void)
{
  XMC_SCU_IRQHandler(2U);
}
#else
/*
 * @brief  IRQ0 Interrupt Handler
 */
void IRQ0_Handler(void)
{
  XMC_SCU_IRQHandler(0);
}

/*  IRQ1 Interrupt Handler.
 *
 */
void IRQ1_Handler(void)
{
  XMC_SCU_IRQHandler(1);
}

/*  IRQ2 Interrupt Handler.
 *
 */
void IRQ2_Handler(void)
{
  XMC_SCU_IRQHandler(2);
}

#endif

/*
 * @brief  Function to register callback event
 */
GLOBAL_SCU_XMC1_STATUS_t GLOBAL_SCU_XMC1_RegisterCallback(const GLOBAL_SCU_XMC1_EVENT_t event,
                                                          const GLOBAL_SCU_XMC1_EVENT_HANDLER_t handler)
{
  GLOBAL_SCU_XMC1_STATUS_t status;

  XMC_ASSERT("GLOBAL_SCU_XMC1_RegisterCallback: Invalid event", (GLOBAL_SCU_XMC1_CHECK_EVENT(event)));
  XMC_ASSERT("GLOBAL_SCU_XMC1_RegisterCallback: NULL Handle", (handler != NULL));
  
  status = (GLOBAL_SCU_XMC1_STATUS_t)XMC_SCU_INTERRUPT_SetEventHandler(event, handler);

  return (status);
}
