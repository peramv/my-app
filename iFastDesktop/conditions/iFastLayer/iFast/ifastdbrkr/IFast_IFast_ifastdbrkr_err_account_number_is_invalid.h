#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_account_number_is_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_account_number_is_invalid() { }
		~CIFast_IFast_ifastdbrkr_err_account_number_is_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_IS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account number is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer ist ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta no es válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer is ongeldig")); }

        // Actions
	};
}



