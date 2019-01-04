#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_err_trade_wire_order_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_err_trade_wire_order_not_allowed() { }
		~CIFast_IFast_ifastcbo_ams_err_trade_wire_order_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_ERR_TRADE_WIRE_ORDER_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS %CODE% does not allow wire orders.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AMS %CODE% does not allow wire orders.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AMS %CODE% does not allow wire orders.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de service de gestion de portefeuille %CODE% n'autorise pas les ordres électroniques.")); }

        // Actions
	};
}



