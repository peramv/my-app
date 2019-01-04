#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ams_acct_should_clone : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ams_acct_should_clone() { }
		~CIFast_IFast_ifastcbo_warn_ams_acct_should_clone() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMS_ACCT_SHOULD_CLONE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account %ACCT% is AMS. The model is set not to be cloned.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte %ACCT% comporte un service de gestion de portefeuille. Le modèle est réglé pour ne pas être cloné.")); }

        // Actions
	};
}



