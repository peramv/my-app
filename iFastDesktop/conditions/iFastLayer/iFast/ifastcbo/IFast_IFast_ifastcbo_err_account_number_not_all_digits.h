#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_number_not_all_digits : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_number_not_all_digits() { }
		~CIFast_IFast_ifastcbo_err_account_number_not_all_digits() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUMBER_NOT_ALL_DIGITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number has to be all digits.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account number has to be all digits.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Kontonummer darf nur aus Ziffern bestehen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta debe tener todos los dígitos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte ne doit être composé que de caractères numériques.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("accountnummer moet alleen cijfers bevatten")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie neu ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul opnieuw in")); }
	};
}



