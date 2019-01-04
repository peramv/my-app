#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_not_active() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ACCT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not active.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account is not active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte inactif")); }

        // Actions
	};
}



