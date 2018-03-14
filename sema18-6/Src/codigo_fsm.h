#include "fsm.h"



/********
 * PARAMETERS DEFINE
 */

#define timeCorrect 1000
#define digit1	1
#define digit2	2
#define digit3	3




/**
 * Structure for the output data
 */
struct fsm_cod_t {
	fsm_t this;
	int code_ok;
};

typedef struct fsm_cod_t fsm_cod_t;


fsm_t* initFSMCod(int* ptr, int dig1, int dig2, int dig3);
void setButtonHigh_1();
void setButtonLow_1();
