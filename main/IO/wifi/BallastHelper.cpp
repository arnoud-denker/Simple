#include "../../main/mkii/IO/wifi/BallastHelper.h"

#define TAG "BALLASTHELPER"

//
//using namespace std;
//
////===========================================
////===========================================
////===========================================
//
//BallastHelper::BallastHelper()
//	{
//	pTemplimits_str = new string("-");
//	pTamb1_str = new string("-");
//	pPercentagelightcurrent_str = new string("-");
//
//	pPowerlightcurrent_str = new string("-");
//	pPercentagelightmax_str = new string("-");
//
//	pTimeleft_str = new string("-");
//	pBallastStatus = new string("-");
//
//	pBallastRunningState_str = new string("-");
//	pBallastHideMaxicontrollermenuDependingRunningState_str = new string("hidden");
//	}
//
////===========================================
////===========================================
////===========================================
////	* pTemplimits_str = tfm::format("Low limit %3d °C, High limit %3d °C, Shutdown limit %3d °C", 21, 25, 29);
//
//string * BallastHelper::get_pTemplimits_str(int8_t lowT, int8_t highT, int8_t shutdownT)
//	{
//	* pTemplimits_str = tfm::format("Low limit %3d °C, High limit %3d °C, Shutdown limit %3d °C", lowT, highT, shutdownT);
//	return pTemplimits_str;
//	}
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pTamb1_str(double tamb1)
//	{
//	*pTamb1_str = tfm::format("%3.1f °C", tamb1);
//	return pTamb1_str;
//	}
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pBallastOutputPercentage_str(int8_t percentageSteering)
//	{
//	*pPercentagelightcurrent_str = tfm::format("%3d %%", percentageSteering);
//	return pPercentagelightcurrent_str;
//	}
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pBallastOutputPower_str(bool hid1Present, uint16_t power1, bool hid2Present, uint16_t power2)
//	{
//	pPowerlightcurrent_str->assign("");
//
//	if (hid1Present == true)
//		{
//		pPowerlightcurrent_str->append(to_string(power1));
//		pPowerlightcurrent_str->append(" W");
//		}
//
//	if (hid1Present == true && hid2Present == true)
//		{
//		pPowerlightcurrent_str->append(", ");
//		}
//
//	if (hid2Present == true)
//		{
//		pPowerlightcurrent_str->append(to_string(power2));
//		pPowerlightcurrent_str->append(" W");
//		}
//
//	return pPowerlightcurrent_str;
//	}
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pBallastStatus_str(bool hid1Present, HidStatusList hidstat1, bool hid2Present, HidStatusList hidstat2)
//	{
//	pBallastStatus->assign("");
//
//	if (hid1Present == true)
//		{
//		pBallastStatus->append(convertStatusToString(hidstat1));
//		}
//
//	if (hid1Present == true && hid2Present == true)
//		{
//		pBallastStatus->append(", ");
//		}
//
//	if (hid2Present == true)
//		{
//		pBallastStatus->append(convertStatusToString(hidstat2));
//		}
//
//	return pBallastStatus;
//	}
//
//
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pPercentagelightmax_str(uint8_t percentagelightmax)
//	{
//	* pPercentagelightmax_str = tfm::format("%3d %%", percentagelightmax);
//
//	return pPercentagelightmax_str;
//	}
//
////===========================================
////===========================================
////===========================================
//
//string * BallastHelper::get_pBallastHideMaxicontrollermenuDependingRunningState_str(RunningStateList currentstate)
//	{
//	if (currentstate == RunningStateList::WIFI || currentstate == RunningStateList::WIFIOFF)
//		{
//		pBallastHideMaxicontrollermenuDependingRunningState_str->assign("visible");
//		}
//	else
//		{
//		pBallastHideMaxicontrollermenuDependingRunningState_str->assign("hidden");
//		}
//
//	return pBallastHideMaxicontrollermenuDependingRunningState_str;
//	}
//
//
////===========================================
////===========================================
////===========================================




