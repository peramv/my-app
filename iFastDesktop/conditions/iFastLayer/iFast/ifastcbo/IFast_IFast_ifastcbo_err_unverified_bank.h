#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_unverified_bank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_unverified_bank() { }
		~CIFast_IFast_ifastcbo_err_unverified_bank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNVERIFIED_BANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Banking information is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Information bancaire non vérifiée")); }

        // Actions
	};
}



