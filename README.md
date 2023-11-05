# buttons
Useful little helper class for evaluating buttons connected to an Arduino.

Usage example:
```cpp
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
```

Some more words:

The init-method also sets the Pullup (if low-active).

The method IsPushedLong() returns "true" for only one cycle.

You can easily use the methods IsPushedLong() and IsReleased() together, the
method IsReleased() will not return "true" if IsPushedLong() was "true" before. 
This is useful when you want to have some kind of memory-button (recall a value
when short pressed, save a value when long pressed)

Because the timing for autorepeat, debounce and longpress is derived from
the repeated calls of the method Readout(), maybe it's a good idea
to use a timer or similar doing this job
