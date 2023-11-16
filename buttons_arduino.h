/*
 * buttons_arduino.h - modified version from
 * buttons.h
 *
 * Created: 08.02.2014 08:52:04
 * Author: mankut
 * Version: 1.2
 
 changelog:
 v1.0.0 - added the static variable "AnyButtonPushed"
 v1.0.1 - 14.12.2014: Bugfix: first call of "readout" delivers correct values now.
 
Usage example:
#include "buttons_arduino.h"

int main(void)
{
	pushbutton mybutton;
	
	mybutton.init(
	2,		//the Arduino-pinnumber, the button is connected to
	0,		//state of the button, when active (pressed)
	10		//debounce-delay (in number of cycles)
	350,	//how many cycles have to occur before Autorepeat starts / before the button is interpreted as "long pressed"
	20		//speed of Autorepeat (in number of cycles) (0 = no autorepeat)
	);

	while(1)
	{
		pushbutton::AnyButtonPushed = 0; //use only if needed
		mybutton.Readout();  //this has to be done first
		
		if (mybutton.IsPushed) do something;
		if (mybutton.IsReleased) do something;
		if (pushbutton::AnyButtonPushed) do something;
		.
		.
		.
	}
}	

Some more words:

The init-method also sets the Pullup (if low-active).

The method IsPushedLong() returns "true" for only one cycle.

You can easily use the methods IsPushedLong() and IsReleased() together, the
method IsReleased() will not return "true" if IsPushedLong() was "true" before. 
This is useful when you want to have some kind of memory-button (recall a value
when short pressed, save a value when long pressed)

Because the timing for autorepeat, debounce and longpress is derived from
the repeated calls of the method Readout(), maybe it's a good idea
to use a timer doing this job
 */ 


#include <Arduino.h>

#ifndef BUTTONS_ARDUINO_H_
#define BUTTONS_ARDUINO_H_


class pushbutton
{
public:
	pushbutton();
	
	void init (uint8_t Inputpin, uint8_t state_when_active, uint16_t debounce, uint16_t autorepeat, uint16_t autorepeat_delay);
	
	void Readout();
	
	uint8_t GetState();
	
	uint8_t IsPushed();
	
	uint8_t IsPushedLong();
	
	uint8_t IsReleased();
	
	uint8_t StateChanged();
	
	static uint8_t AnyButtonPushed;
	
protected:
	uint8_t pin;
	
private:
	uint8_t activestate;		//whether the button delivers 0 or 1 when pressed
	uint8_t state;				//the actual state (pressed (1) or not (0))
	uint8_t state_before;		//the state it had before
	uint16_t cyclecounter;		//counting the "button is pressed"-cycles
	uint16_t debouncecycles;	//minimum number of cycles, the button has to be pressed
	uint16_t autorepeatstart;	//number of cycles for start of autorepeat / longpressmarker
	uint16_t autorepeatdelay;	//number of cycles for the delay between each autorepeat
	uint16_t pushedlongmark;
	
};



#endif /* BUTTONS_H_ */
