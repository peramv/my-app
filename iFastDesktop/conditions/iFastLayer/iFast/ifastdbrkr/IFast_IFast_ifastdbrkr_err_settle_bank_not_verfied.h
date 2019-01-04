#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_settle_bank_not_verfied : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_settle_bank_not_verfied() { }
		~CIFast_IFast_ifastdbrkr_err_settle_bank_not_verfied() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_BANK_NOT_VERFIED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Banking information is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information bancaire non vérifiée")); }

        // Actions
	};
}



