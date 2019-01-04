#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trading_time_passed_aggregated_order_cutoff_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trading_time_passed_aggregated_order_cutoff_time() { }
		~CIFast_IFast_ifastcbo_warn_trading_time_passed_aggregated_order_cutoff_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADING_TIME_PASSED_AGGREGATED_ORDER_CUTOFF_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading time passed aggregated order cut-off time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trading time passed aggregated order cut-off time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le délai de l'opération a dépassé l'heure limite de l'ordre global.")); }

        // Actions
	};
}



