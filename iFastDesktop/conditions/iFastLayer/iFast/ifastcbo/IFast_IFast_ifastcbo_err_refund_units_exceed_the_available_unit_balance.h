#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_refund_units_exceed_the_available_unit_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_refund_units_exceed_the_available_unit_balance() { }
		~CIFast_IFast_ifastcbo_err_refund_units_exceed_the_available_unit_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REFUND_UNITS_EXCEED_THE_AVAILABLE_UNIT_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Refund units exceeds the available unit balance of the linked purchase.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Refund units exceeds the available unit balance of the linked purchase.")); }

        // Actions
	};
}