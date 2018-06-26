
#include "led_fsm.h"
#include "fsm.h"
#include "stm32f0xx_hal.h"
#include "stddef.h"

/*
 * Functions declarations
 */
static void buttonON(fsm_t* this);
static void buttonOFF(fsm_t* this);
static int buttonPressed (fsm_t* this);
static int timeFinish(fsm_t* this);

static int button=0;
uint32_t reference,now;



/**
 * Function to initialize the FSM
 * We pass for reference the direction of the FSM.
 */
fsm_t* initFSMLed(){
	fsm_t* result;

	/**
	 * We defined the states
	 */
	enum semp_state {
	  ON,
	  OFF,
	};

	/**
	 * We defined the transition table
	 */

	static fsm_trans_t led[] = {
	  {OFF, buttonPressed, ON , buttonON},
	  {ON , buttonPressed, OFF, buttonOFF},
	  {ON , timeFinish, OFF, buttonOFF},
	  {-1, NULL, -1, NULL },
	};

	result=fsm_new(led);

	return result;
}

static int buttonPressed (fsm_t* this) {
	return button;
}


static void buttonOFF(fsm_t* this){
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,0U);
	setButtonLow();
}

static int timeFinish(fsm_t* this){
	int result=0;

	now= HAL_GetTick();

	if (now - timeLed >= reference)
		result=1;

	return result;
}

static void buttonON(fsm_t* this){
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,1U);
	setButtonLow();

	reference=HAL_GetTick();	// Start the time
}

void setButtonHigh(){
	button=1;
}

void setButtonLow(){
	button=0;
}
