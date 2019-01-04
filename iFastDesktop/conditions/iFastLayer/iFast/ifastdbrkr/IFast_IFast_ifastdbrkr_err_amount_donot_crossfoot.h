#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amount_donot_crossfoot : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amount_donot_crossfoot() { }
		~CIFast_IFast_ifastdbrkr_err_amount_donot_crossfoot() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_DONOT_CROSSFOOT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The entered amounts do not crossfoot.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les montants saisis ne balancent pas.")); }

        // Actions
	};
}



