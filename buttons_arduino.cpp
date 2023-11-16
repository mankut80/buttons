/*
 * buttons_arduino.cpp
 *
 * Created: 08.02.2014 09:10:16
 *  Author: mankut
 * v1.0.1
 */ 

#include <avr/io.h>
#include <Arduino.h>
#include "iohelper.h"
#include "buttons_arduino.h"

uint8_t pushbutton::AnyButtonPushed = 0;

pushbutton::pushbutton()
{
};

void pushbutton::init (uint8_t Inputpin, uint8_t state_when_active, uint16_t debounce, uint16_t autorepeat, uint16_t autorepeat_delay)
{
	if (state_when_active){
		pinMode(Inputpin,INPUT);
	}
	else{
		pinMode(Inputpin,INPUT_PULLUP);
	} 
			
	activestate = state_when_active;
	
	state = digitalRead(Inputpin);
	state_before = state;
	autorepeatstart = autorepeat;
	autorepeatdelay = autorepeat_delay;
	debouncecycles = debounce;
	pin=Inputpin;
	pushbutton::Readout();
}

void pushbutton::Readout()
{
	state_before = state;
	
	if (digitalRead(pin) == activestate)
	{
		cyclecounter++;
		
		if(cyclecounter >= debouncecycles)
		{
			state = 1;
			pushbutton::AnyButtonPushed = 1;
		}
		
		if(cyclecounter == autorepeatstart) 
		{
			pushedlongmark = 1;
		}
		else
		{
			if (pushedlongmark) pushedlongmark = 2;
		}		
		
	}
	else
	{
		state = 0;
		cyclecounter = 0;
	}
	
	if (cyclecounter == 0xFFFF) cyclecounter = 0xFFFE;
	
	
}

uint8_t pushbutton::GetState()
{
	if (state == activestate)
		{return 1;}	else {return 0;}
			
	return 0;
}

uint8_t pushbutton::StateChanged()
{
	if (state_before == state) return 0;
	return 1;
}

uint8_t pushbutton::IsPushed()
{
		
	if (state_before < state)
	{
		return 1;
	}	
	
	if (autorepeatdelay)
	{
		if (cyclecounter >= autorepeatstart)
		{
			cyclecounter -= autorepeatdelay;
			return 1;
		}
	}
	return 0;
}

uint8_t pushbutton::IsPushedLong()
{
	if (pushedlongmark == 1) return 1;
	return 0;
}


uint8_t pushbutton::IsReleased()
{
	if ((state_before > state) && (pushedlongmark == 0))
	{
		return 1;
	}
	else
	{
		if (state_before < state) pushedlongmark = 0;
	}	
	return 0;
}
