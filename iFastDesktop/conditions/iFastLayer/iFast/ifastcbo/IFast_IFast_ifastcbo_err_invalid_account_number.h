#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_account_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_account_number() { }
		~CIFast_IFast_ifastcbo_err_invalid_account_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ACCOUNT_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid account number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Kontonummer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de cuenta no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig accountnummer")); }

        // Actions
	};
}



