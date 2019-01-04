#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_categ_puev_should_be_setup_based_on_clearingid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_categ_puev_should_be_setup_based_on_clearingid() { }
		~CIFast_IFast_ifastcbo_warn_acct_categ_puev_should_be_setup_based_on_clearingid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_CATEG_PUEV_SHOULD_BE_SETUP_BASED_ON_CLEARINGID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account category PUEV should be setup when account clearingID is PUEV")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account category PUEV should be setup when account clearingID is PUEV")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie de compte PUEV devrait être réglée lorsque le code de compensation du compte est PUEV.")); }

        // Actions
	};
}



