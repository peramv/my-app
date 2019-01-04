#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_wire_order_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_wire_order_trade() { }
		~CIFast_IFast_ifastdbrkr_err_not_wire_order_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_WIRE_ORDER_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This is not wire order trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci n'est pas une transaction d'ordre électronique.")); }

        // Actions
	};
}



