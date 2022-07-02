/******************************************************************************
 *
 * Module: ICU
 *
 * File Name: icu.h
 *
 * Description: Header file for ICU driver
 *
 * Date Created: 12/10/2021
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#ifndef ICU_H_
#define ICU_H_
#include "std_types.h"
/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/* Pre-scaler clock options for Timer1*/
typedef enum {
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
} ICU_Clock;
/* ICU trigger edge type */
typedef enum {
	FALLING, RISING
} ICU_EdgeType;
/******************************************************************************
 *
 * Structure Name: Icu_ConfigType
 *
 * Structure Description:  Configuration struct for initializing ICU driver
 *
 *******************************************************************************/

typedef struct {
	ICU_Clock clock; /* Pre-scaler for timer1 clock */
	ICU_EdgeType edge; /* Edge trigger type for ICU*/
} ICU_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/******************************************************************************
 *
 * Function Name: ICU_init
 *
 * Description:  Initializes ICU using configuration struct, sets pre-scaler,
 * 			sets ICU edge trigger type, clears timer1 registers & sets ICU pin to i/p
 *
 * Args:
 *
 * 		[in] const Icu_ConfigType *Config_Ptr
 * 			Struct which contains the configuration options
 * 		[out] N/A
 * Returns: void
 *******************************************************************************/
void ICU_init(const ICU_ConfigType *Config_Ptr);

/******************************************************************************
 *
 * Function Name: ICU_setCallBack
 *
 * Description:  Sets callback function which executes after ICU interrupt
 *
 * Args:
 *
 * 		[in] (*a_ptr)(void)
 * 			Pointer to the passed callback function
 * 		[out] N/A
 * Returns: void
 *******************************************************************************/
void ICU_setCallBack(void (*a_ptr)(void));

/******************************************************************************
 *
 * Function Name: ICU_setEdgeDetectionType
 *
 * Description:  Sets the edge type which triggers an ICU interrupt
 *
 * Args:
 *
 * 		[in] const Icu_EdgeType a_edgeType
 * 			Edge type (FALLING/RISING)
 * 		[out] N/A
 * Returns: void
 *******************************************************************************/
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType);

/******************************************************************************
 *
 * Function Name: ICU_getInputCaptureValue
 * Description:  Returns ICR register which contains last captured value
 * Args: void
 * Returns: void
 *******************************************************************************/
uint16 ICU_getInputCaptureValue(void);

/******************************************************************************
 *
 * Function Name: ICU_clearTimerValue
 * Description:  Clears timer counter register
 * Args: void
 * Returns: void
 *******************************************************************************/
void ICU_clearTimerValue(void);

/******************************************************************************
 *
 * Function Name: ICU_DeInit
 * Description:  De-initializes ICU, disables Timer1 & turns of ICU interrupt
 * Args: void
 * Returns: void
 *******************************************************************************/
void ICU_DeInit(void);

#endif /* ICU_H_ */
