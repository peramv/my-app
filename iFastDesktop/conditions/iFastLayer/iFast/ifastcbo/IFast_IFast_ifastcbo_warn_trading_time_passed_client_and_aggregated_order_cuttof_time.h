#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trading_time_passed_client_and_aggregated_order_cuttof_time : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trading_time_passed_client_and_aggregated_order_cuttof_time() { }
		~CIFast_IFast_ifastcbo_warn_trading_time_passed_client_and_aggregated_order_cuttof_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADING_TIME_PASSED_CLIENT_AND_AGGREGATED_ORDER_CUTTOF_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trading time passed client and aggregated order cut-off time.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Trading time passed client and aggregated order cut-off time.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le délai de l'opération a dépassé l'heure limite du client et de l'ordre global.")); }

        // Actions
	};
}



