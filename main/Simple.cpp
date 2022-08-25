#include "Simple.h"


#define TAG "SIMPLE"


Simple::Simple()
	{
	pWifiuserland = new WifiUserland();
	}

Simple::~Simple()
	{

	}

void Simple::init()
	{
	pWifiuserland->wifi_init();
	}

void Simple::start()
	{

	}

//==========================================================================
//==========================================================================
//==========================================================================
