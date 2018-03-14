/*
 * alarm_fsm.h
 *
 *  Created on: 6 mar. 2018
 *      Author: Salva
 */

#include "fsm.h"


struct fsm_alarm_t {
	fsm_t this;
	int *code_ok;
};

typedef struct fsm_alarm_t fsm_alarm_t;


fsm_t* initFSMAlarm(int *ptr);


