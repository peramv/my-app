#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctholder_over_age_for_protected_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctholder_over_age_for_protected_fund() { }
		~CIFast_IFast_ifastcbo_err_acctholder_over_age_for_protected_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTHOLDER_OVER_AGE_FOR_PROTECTED_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account owner must be less than 80 years old for trading Protected Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account owner must be less than 80 years old for trading Protected Fund.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Account owner must be less than 80 years old for trading Protected Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le titulaire du compte doit être âgé de moins de 80 ans pour procéder à une opération de fonds protégés.")); }

        // Actions
	};
}



