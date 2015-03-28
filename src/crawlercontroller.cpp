// -*- C++ -*-
/*!
 * @file  crawlercontroller.cpp
 * @brief Crawler Controller Component
 * @date $Date$
 *
 * $Id$
 */

#include "crawlercontroller.h"

// Module specification
// <rtc-template block="module_spec">
static const char* crawlercontroller_spec[] =
  {
    "implementation_id", "crawlercontroller",
    "type_name",         "crawlercontroller",
    "description",       "Crawler Controller Component",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "TES",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.motor0in0", "2",
    "conf.default.motor0in1", "4",
    "conf.default.motor0pwm", "3",
    "conf.default.motor1in0", "5",
    "conf.default.motor1in1", "8",
    "conf.default.motor1pwm", "6",
    // Widget
    "conf.__widget__.motor0in0", "text",
    "conf.__widget__.motor0in1", "text",
    "conf.__widget__.motor0pwm", "text",
    "conf.__widget__.motor1in0", "text",
    "conf.__widget__.motor1in1", "text",
    "conf.__widget__.motor1pwm", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
crawlercontroller::crawlercontroller(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_in0In("in0", m_in0),
    m_in1In("in1", m_in1)

    // </rtc-template>
{
	controller0 = NULL;
	controller1 = NULL;
}

/*!
 * @brief destructor
 */
crawlercontroller::~crawlercontroller()
{
}



RTC::ReturnCode_t crawlercontroller::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in0", m_in0In);
  addInPort("in1", m_in1In);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("motor0in0", m_motor0in0, "2");
  bindParameter("motor0in1", m_motor0in1, "4");
  bindParameter("motor0pwm", m_motor0pwm, "3");
  bindParameter("motor1in0", m_motor1in0, "5");
  bindParameter("motor1in1", m_motor1in1, "8");
  bindParameter("motor1pwm", m_motor1pwm, "6");
  
  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t crawlercontroller::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t crawlercontroller::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t crawlercontroller::onShutdown(RTC::UniqueId ec_id)
{
	if(controller0)
	{
		delete controller0;
	}
	if(controller1)
	{
		delete controller1;
	}

  return RTC::RTC_OK;
}


RTC::ReturnCode_t crawlercontroller::onActivated(RTC::UniqueId ec_id)
{
	mraa_result_t response;
	if(controller0 == NULL)
	{
		controller0 = new Crawler_Controller(response, m_motor0pwm, m_motor0in0, m_motor0in1);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
	if(controller1 == NULL)
	{
		controller1 = new Crawler_Controller(response, m_motor1pwm, m_motor1in0, m_motor1in1);
		if(response != MRAA_SUCCESS)
		{
			return RTC::RTC_ERROR;
		}
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t crawlercontroller::onDeactivated(RTC::UniqueId ec_id)
{
	controller0->setValue(0);
	controller1->setValue(0);
  return RTC::RTC_OK;
}


RTC::ReturnCode_t crawlercontroller::onExecute(RTC::UniqueId ec_id)
{
	if(m_in0In.isNew())
	{
		m_in0In.read();
		controller0->setValue(m_in0.data);
	}
	if(m_in1In.isNew())
	{
		m_in1In.read();
		controller1->setValue(m_in1.data);
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t crawlercontroller::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t crawlercontroller::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t crawlercontroller::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t crawlercontroller::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t crawlercontroller::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void crawlercontrollerInit(RTC::Manager* manager)
  {
    coil::Properties profile(crawlercontroller_spec);
    manager->registerFactory(profile,
                             RTC::Create<crawlercontroller>,
                             RTC::Delete<crawlercontroller>);
  }
  
};


