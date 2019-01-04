#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_invalid_for_this_shr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_invalid_for_this_shr() { }
		~CIFast_IFast_ifastcbo_err_acct_invalid_for_this_shr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_INVALID_FOR_THIS_SHR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account %ACCOUNT_NUM% invalid for this shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account %ACCOUNT_NUM% invalid for this shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Konto %ACCOUNT_NUM% ist für diesen Aktionär ungültig. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta %ACCOUNT_NUM% no es válida para este accionista. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte %ACCOUNT_NUM% est invalide pour cet actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account %ACCOUNT_NUM% is ongeldig voor deze aandeelhouder. Vul opnieuw in")); }

        // Actions
	};
}



