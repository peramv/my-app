#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_aggregated_order_trade_date_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_aggregated_order_trade_date_invalid() { }
		~CIFast_IFast_ifastcbo_err_aggregated_order_trade_date_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGGREGATED_ORDER_TRADE_DATE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid trade date for this aggregated order.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid trade date for this aggregated order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de transaction invalide pour cet ordre global")); }

        // Actions
	};
}



