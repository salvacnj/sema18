
#include "alarm_fsm.h"
#include "fsm.h"
#include "stddef.h"
#include "stm32f0xx_hal.h"

/***
 * Global variables declaration for timing
 */


/*
 * Functions declarations
 */
static void LedON(fsm_t* this);
static void LedOFF(fsm_t* this);
static int armada (fsm_t* this);
static int IR (fsm_t* this);
static int notArmada (fsm_t* this);
static int notIR (fsm_t* this);




/**
 * Function to initialize the FSM
 * We pass for reference the direction of the FSM.
 */
fsm_t* initFSMAlarm(){
	fsm_t* result;

	/**
	 * We defined the states
	 */
	enum semp_state {
	  ALARM_OFF,
	  ALARM_ON,
	  LED_ON,
	};

	/**
	 * We defined the transition table
	 */

	static fsm_trans_t alarm_trans[] = {
	  {ALARM_OFF, armada , ALARM_ON  ,   NULL	},
	  {ALARM_ON , notArmada, ALARM_OFF ,   NULL	},
	  {ALARM_ON , IR	 , LED_ON    , LedON},
	  {LED_ON   , notIR , ALARM_ON  , LedOFF},
	  {LED_ON   , notArmada  , ALARM_OFF , LedOFF},
	  {-1, NULL, -1, NULL },
	};

	result=fsm_new(alarm_trans);

	return result;
}


static int notArmada (fsm_t* this){
	if(HAL_GPIO_ReadPin(ARMADA_GPIO_Port, ARMADA_Pin)==0)
		return 1;
	else
		return 0;

}
static int armada (fsm_t* this){

	if(HAL_GPIO_ReadPin(ARMADA_GPIO_Port, ARMADA_Pin)==0)
		return 0;
	else
		return 1;
}

static int IR (fsm_t* this){

	if(HAL_GPIO_ReadPin(IR_GPIO_Port, IR_Pin)==0)
		return 0;
	else
		return 1;
}

static int notIR (fsm_t* this){

	if(HAL_GPIO_ReadPin(IR_GPIO_Port, IR_Pin)==0)
		return 1;
	else
		return 0;
}

static void LedON(fsm_t* this){
	HAL_GPIO_WritePin(ALARM_GPIO_Port,ALARM_Pin,1U);
}

static void LedOFF(fsm_t* this){
	HAL_GPIO_WritePin(ALARM_GPIO_Port,ALARM_Pin,0U);
}










