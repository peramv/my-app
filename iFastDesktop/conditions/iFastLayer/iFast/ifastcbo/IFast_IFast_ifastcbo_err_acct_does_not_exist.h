#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_does_not_exist() { }
		~CIFast_IFast_ifastcbo_err_acct_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account %ACCOUNT_NUM% does not exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le compte %ACCOUNT_NUM% n'existe pas. Veuillez ressaisir un numero de compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Konto %ACCOUNT_NUM% existiert nicht. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta %ACCOUNT_NUM% no existe. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte %ACCOUNT_NUM% n'existe pas.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account %ACCOUNT_NUM% bestaat niet. Vul opnieuw in")); }

        // Actions
	};
}



