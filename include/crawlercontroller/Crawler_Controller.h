#ifndef Crawler_Controller_H
#define Crawler_Controller_H

#include <stdio.h>
#include <mraa.hpp>




class Crawler_Controller
{
public:
	Crawler_Controller(mraa_result_t &response, int pwm_pin = 3, int in0_pin = 2, int in1_pin = 4);
	~Crawler_Controller();
	void setValue(double vol);
	
private:
	mraa::Pwm* pwm;
	mraa::Gpio* in0;
	mraa::Gpio* in1;
};





#endif