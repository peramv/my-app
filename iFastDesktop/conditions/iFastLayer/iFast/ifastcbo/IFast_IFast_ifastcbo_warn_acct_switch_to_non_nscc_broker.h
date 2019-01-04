#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_switch_to_non_nscc_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_switch_to_non_nscc_broker() { }
		~CIFast_IFast_ifastcbo_warn_acct_switch_to_non_nscc_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_SWITCH_TO_NON_NSCC_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Account has a NON_NSCC broker and the corresponding fields will be blank out,")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account has been swiched to a non-NSCC broker and the corresponding fields being blank out,")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier du compte n'est pas NSCC et les champs correspondants seront laissés vides.")); }

        // Actions
	};
}



