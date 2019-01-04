#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_category_not_allowed_for_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_category_not_allowed_for_account() { }
		~CIFast_IFast_ifastcbo_err_acct_category_not_allowed_for_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_CATEGORY_NOT_ALLOWED_FOR_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Category not allowed for the account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Catégorie de compte non autorisée pour le compte")); }

        // Actions
	};
}



