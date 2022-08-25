#ifndef _Simple_H_
#define _Simple_H_


#include "IO/wifi/WifiUserland.h"




class Simple
	{
	public:
		Simple();
		virtual ~Simple();

		void init();
		void start();

	private:
		WifiUserland * pWifiuserland = nullptr;		// todo nullptr... with defines?
	};


#endif
