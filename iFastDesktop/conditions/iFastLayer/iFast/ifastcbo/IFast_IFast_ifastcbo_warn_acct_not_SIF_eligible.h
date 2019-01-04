#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_not_SIF : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_not_SIF() { }
		~CIFast_IFast_ifastcbo_warn_acct_not_SIF() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_NOT_SIF_ELIGABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not SIF eligible.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account is not SIF eligible.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account is not SIF eligible.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte est pas SIF éligibles .")); }

        // Actions
	};
}



