


#include "stdbool.h"
#include "codigo_fsm.h"
#include "stm32f0xx_hal.h"
#include "fsm.h"



/**
 * Variables for the timer
 */
bool enable_timer=false;
uint32_t	now,reference;

/*
 * Variable for the button
 */
static int button=0;

/**
 * Variable for the count
 */
static int cont=0;

/**
 * Pointer to the Code_OK
 */
static int* ptr_code;

/**
 * Variables to save de digit
 */
int dig[3];
int i=0;




/*
 * Functions definition
 */

static int OneSecondElapsed(fsm_t* this);
static void buttonLow(fsm_t* this);
static int buttonPressed (fsm_t* this);
void setCont(int n);
static void func1 (fsm_t* this);
static void func2(fsm_t* this);
static void func3(fsm_t* this);
static int ContBiggerDig(fsm_t* this);
static int ContEqualDig(fsm_t* this);
static void push(fsm_t* this);
static void codeOK(fsm_t* this);
void timer_start();
void timer_stop();
static int trueF(fsm_t* this);



/**
 * Timing functions
 */
void timer_start(){
	enable_timer=true;
	reference = HAL_GetTick();
}

void timer_stop(){
	enable_timer=false;
}









/**
 * Function to initialize the FSM
 */
fsm_t* initFSMCod(int* ptr, int dig1, int dig2, int dig3){

	fsm_t* this;

	dig[0]=dig1;
	dig[1]=dig2;
	dig[2]=dig3;
	ptr_code=ptr;
	*ptr_code=0;


	/**
		 * We defined the states
		 */
		enum semp_state {
		  WAIT,
		  CHECK_1,
		  WAIT_1,
		  CHECK_2,
		  WAIT_2,
		  CHECK_3,
		  WAIT_3,
		  CODE_OK
		};

		/**
		 * We defined the transition table
		 */

		static fsm_trans_t code[] = {
		  {WAIT, 		buttonPressed, 		CHECK_1 , 		func1},
		  {CHECK_1, 	OneSecondElapsed, 	WAIT ,			 NULL},
		  {CHECK_1, 	ContBiggerDig,		WAIT ,			 NULL},
		  {CHECK_1, 	buttonPressed,		CHECK_1 ,		push},
		  {CHECK_1, 	ContEqualDig    ,	WAIT_1  , 		NULL},
		  {WAIT_1 , 	OneSecondElapsed   ,CHECK_2 , 		func2},
		  {WAIT_1 , 	buttonPressed      ,WAIT   , 		buttonLow},
		  {CHECK_2, 	OneSecondElapsed,	WAIT    , 		NULL},
		  {CHECK_2, 	ContBiggerDig,		WAIT ,			 NULL},
		  {CHECK_2, 	buttonPressed,		CHECK_2 ,		push},
		  {CHECK_2, 	ContEqualDig,		WAIT_2 ,		NULL},
		  {WAIT_2 , 	OneSecondElapsed   ,CHECK_3 , 		func3},
		  {WAIT_2 , 	buttonPressed      ,WAIT   , 		buttonLow},
		  {CHECK_3, 	OneSecondElapsed,	WAIT    , 		NULL},
		  {CHECK_3, 	ContBiggerDig,		WAIT ,			 NULL},
		  {CHECK_3, 	buttonPressed,		CHECK_3 ,		push},
		  {CHECK_3, 	ContEqualDig,		WAIT_3 ,		NULL},
		  {WAIT_3 , 	OneSecondElapsed   ,CODE_OK , 		codeOK},
		  {WAIT_3 , 	buttonPressed      ,WAIT   , 		buttonLow},
		  {CODE_OK, 	trueF		,		WAIT   ,		NULL},
		  {-1, NULL, -1, NULL },
		};

	this=fsm_new(code);

	return this;
}





/***************************************************
 * 				Actions FSM
 **************************************************/

static void func1 (fsm_t* this){
	// Set botton LOW
	setButtonLow_1();
	// Cont set to 1 to count the first pulse
	setCont(1);
	// Start the 1 second count
	timer_start();
	// Checking the first digit
	i=0;
}

static void buttonLow(fsm_t* this){
	setButtonLow_1();
}

static void push(fsm_t* this){
	setButtonLow_1();
	cont++;
	timer_start();
}

static void func2(fsm_t* this){
	// Cont set to 0
	setCont(0);
	// Waitin pulse
	timer_stop();
	// Checking the second digit
	i=1;
}

static void func3(fsm_t* this){
	// Cont set to 0
	setCont(0);
	// Waitin pulse
	timer_stop();
	// Checking the second digit
	i=2;

}

static void codeOK(fsm_t* this){

	if (*ptr_code == 1)
		*ptr_code=0;
	else
		*ptr_code=1;
}



/***************************************************
 * 				Conditions FSM
 **************************************************/

static int trueF(fsm_t* this){
	return 1;
}

static int ContEqualDig(fsm_t* this){
	if (cont == dig[i])
		return 1;
	else
		return 0;
}

static int ContBiggerDig(fsm_t* this){
	if (cont > dig[i])
		return 1;
	else
		return 0;
}

static int OneSecondElapsed(fsm_t* this){
	int result=0;

	if (enable_timer==true){
		now= HAL_GetTick();

		if (now - timeCorrect >= reference)
			result=1;

		return result;
	} else
		return 0;
}

static int buttonPressed (fsm_t* this) {
	return button;
}
/**
 * Program Functions
 */

/**
 * Set the cont variable to a value n
 */
void setCont(int n){
	cont=n;
}


/**
 * Set the High/Low level of the button
 */
void setButtonHigh_1(){
	button=1;
}

void setButtonLow_1(){
	button=0;
}







