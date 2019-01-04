#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_spouse : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_spouse() { }
		~CIFast_IFast_ifastcbo_err_warn_account_type_must_be_individual_spouse() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_ACCOUNT_TYPE_MUST_BE_INDIVIDUAL_SPOUSE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The account type must be individual or spousal.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Konto muss für eine Einzelperson oder einen Ehepartner eingerichtet sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cuenta debe ser Individual o Conyugal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de compte doit être Individuel ou Conjoint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het accounttype moet individueel of echtelijk zijn")); }

        // Actions
	};
}



