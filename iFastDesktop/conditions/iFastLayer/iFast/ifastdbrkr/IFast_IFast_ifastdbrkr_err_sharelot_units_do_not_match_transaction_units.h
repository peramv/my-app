#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_sharelot_units_do_not_match_transaction_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_sharelot_units_do_not_match_transaction_units() { }
		~CIFast_IFast_ifastdbrkr_err_sharelot_units_do_not_match_transaction_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHARELOT_UNITS_DO_NOT_MATCH_TRANSACTION_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("ShareLot Units do not match Transaction Units.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("ShareLot Units do not match Transaction Units.")); }

        // Actions
	};
}



