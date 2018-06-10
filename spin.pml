mtype = {LED_ON, LED_OFF}
mtype = {DESARMADA, ARMADA, ALARMA}


ltl spec {
	( [] (((state == LED_OFF) && button) -> <> (state == LED_ON)) ) &&
	( [] (((state == LED_ON) && button) -> <> (state == LED_OFF)) ) &&

	( [] ((state_alarm == ARMADA && presencia) -> <>(state_alarm == ALARMA)))
}

bit button, time_elapsed, code_ok, presencia;
int state, state_alarm;

active proctype led_fsm (){

	state = LED_OFF;

	do
	:: (state == LED_OFF) -> atomic {
		if
		:: button -> state = LED_ON; button = 0
		fi
	}
	:: (state == LED_ON) -> atomic {
		if
		:: (button || time_elapsed) -> state = LED_OFF; button = 0
		fi
	}
	od

}

active proctype alarm_fsm (){

	state_alarm = DESARMADA;

	do
	:: (state_alarm == DESARMADA) -> atomic{
		if
		:: code_ok -> state_alarm = ARMADA; code_ok = 0
		fi
	}
	:: (state_alarm == ARMADA) -> atomic{
		if
		:: code_ok && !presencia -> state_alarm = DESARMADA; code_ok = 0
		:: presencia -> state_alarm = ALARMA; presencia = 0
		fi
	}
	:: (state_alarm == ALARMA) -> atomic {
		if
		:: code_ok -> state_alarm == DESARMADA; code_ok = 0;
		fi
	}
	od
}

active proctype code_fsm(){
	do
	:: code_ok = 1
	:: code_ok = 0
	od
}

active proctype entorno (){
	do
	:: if
	   :: button = 1
	   :: presencia = 1
	   :: time_elapsed = 1
	   :: skip
	   fi 
	   printf ("state =%d, button = %d\n", state, button)
	od
} 
