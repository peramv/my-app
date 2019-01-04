#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_to_is_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_to_is_invalid() { }
		~CIFast_IFast_ifastcbo_err_acct_to_is_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_TO_IS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please enter a valid Account To number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte geben Sie eine gültige KontoZu-Nummer ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor introduzca un número de cuenta de destino válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez entrer un numéro Compte vers valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vul een geldig nummer in voor het naar-account")); }

        // Actions
	};
}



