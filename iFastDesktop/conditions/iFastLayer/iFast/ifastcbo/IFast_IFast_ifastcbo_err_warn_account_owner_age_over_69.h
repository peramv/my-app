#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_account_owner_age_over_69 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_account_owner_age_over_69() { }
		~CIFast_IFast_ifastcbo_err_warn_account_owner_age_over_69() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCOUNT_OWNER_AGE_OVER_69")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account owner's age is over 71.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Alter des Kontoinhabers liegt über 71.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El propietario de la cuenta tiene más de 71 años.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du compte est âgé de plus de 71 ans.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Leeftijd van accounthouder ligt boven de 71")); }

        // Actions
	};
}



