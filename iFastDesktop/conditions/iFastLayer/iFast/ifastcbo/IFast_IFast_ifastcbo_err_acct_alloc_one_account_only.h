#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_alloc_one_account_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_alloc_one_account_only() { }
		~CIFast_IFast_ifastcbo_err_acct_alloc_one_account_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_ALLOC_ONE_ACCOUNT_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only one account at 100% is allowed for this allocation type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Only one account at 100% is allowed for this allocation type.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Only one account at 100% is allowed for this allocation type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un seul compte à 100 % est autorisé pour ce type de répartition.")); }

        // Actions
	};
}



