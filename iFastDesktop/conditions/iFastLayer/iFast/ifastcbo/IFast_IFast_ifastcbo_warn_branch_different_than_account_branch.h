#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_branch_different_than_account_branch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_branch_different_than_account_branch() { }
		~CIFast_IFast_ifastcbo_warn_branch_different_than_account_branch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BRANCH_DIFFERENT_THAN_ACCOUNT_BRANCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Branch of account and transaction are different.")); }
        virtual DString GetMessage_FR_CA() const { return DString(I_("The Branch of account and transaction are different.")); }

        // Actions
	};
}



