#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_switch_to_nscc_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_switch_to_nscc_broker() { }
		~CIFast_IFast_ifastcbo_warn_acct_switch_to_nscc_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_SWITCH_TO_NSCC_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The Account has a NSCC broker. Go to COA screen to enter NSCC information.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The Account has been switched to a NSCC broker. Go to COA screen to enter NSCC information.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier du compte est NSCC. Allez à l'écran Avertissement/Option/Attributs et entrez l'information NSCC.")); }

        // Actions
	};
}



