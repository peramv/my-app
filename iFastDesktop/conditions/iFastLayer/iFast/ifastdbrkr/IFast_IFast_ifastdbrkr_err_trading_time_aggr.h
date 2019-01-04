#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trading_time_aggr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trading_time_aggr() { }
		~CIFast_IFast_ifastdbrkr_err_trading_time_aggr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADING_TIME_AGGR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading time passed Aggregate Cute Off time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trading time passed Aggregate Cute Off time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le délai de l'opération a dépassé l'heure limite globale.")); }

        // Actions
	};
}



