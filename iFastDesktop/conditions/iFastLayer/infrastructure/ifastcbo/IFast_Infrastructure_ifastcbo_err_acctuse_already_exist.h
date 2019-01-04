#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_acctuse_already_exist : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_acctuse_already_exist() { }
		~CIFast_Infrastructure_ifastcbo_err_acctuse_already_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTUSE_ALREADY_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entry of zip code is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entry of zip code is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eingabe einer Postleitzahl ist ungültig. Bestätigen Sie die Postleitzahl und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal introducido no es válido. Verifique el código postal y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisie de code postal invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoer van postcode is ongeldig. Controleer de postcode en voer deze opnieuw in")); }

        // Actions
	};
}



