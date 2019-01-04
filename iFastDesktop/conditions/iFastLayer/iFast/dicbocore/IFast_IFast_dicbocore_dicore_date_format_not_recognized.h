#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_dicore_date_format_not_recognized : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_dicore_date_format_not_recognized() { }
		~CIFast_IFast_dicbocore_dicore_date_format_not_recognized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DATE_FORMAT_NOT_RECOGNIZED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
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



