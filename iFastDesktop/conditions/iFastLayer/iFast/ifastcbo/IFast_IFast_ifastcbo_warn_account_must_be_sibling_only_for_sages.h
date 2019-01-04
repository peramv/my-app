#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_must_be_sibling_only_for_sages : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_must_be_sibling_only_for_sages() { }
		~CIFast_IFast_ifastcbo_warn_account_must_be_sibling_only_for_sages() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ACCOUNT_MUST_BE_SIBLING_ONLY_FOR_SAGES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account must be Sibling Only for SAGES.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte doit être de type frère/sœur pour la SEEAS.")); }

        // Actions
	};
}



