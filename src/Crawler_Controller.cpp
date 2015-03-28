#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "Crawler_Controller.h"

Crawler_Controller::Crawler_Controller(mraa_result_t &response, int pwm_pin, int in0_pin, int in1_pin) {
	
	pwm = new mraa::Pwm(pwm_pin);
	if (pwm == NULL) {
        	response = MRAA_ERROR_UNSPECIFIED;
		return;
    	}
	pwm->enable(true);

	in0 = new mraa::Gpio(in0_pin);
	response = in0->dir(mraa::DIR_OUT);
	
	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}

	in1 = new mraa::Gpio(in1_pin);
	response = in1->dir(mraa::DIR_OUT);

	if (response != MRAA_SUCCESS) {
        	mraa::printError(response);
        	return;
    	}

	response = MRAA_SUCCESS;
}

Crawler_Controller::~Crawler_Controller() {
	in0->write(0);
	pwm->write(0);
	in1->write(0);
	pwm->enable(false);
	delete pwm;
	delete in0;
	delete in1;
}

void Crawler_Controller::setValue(double vol) {
	if(vol < 0)
	{
		in0->write(1);
		pwm->write(-vol);
		in1->write(0);
	}
	else
	{
		in0->write(0);
		pwm->write(vol);
		in1->write(1);
	}
}
