#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_invalid_zipcode : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_invalid_zipcode() { }
		~CIFast_Infrastructure_ditabuscore_err_invalid_zipcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ZIPCODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entry of zip code is invalid. Verify zip code and re-enter.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entry of zip code is invalid. Verify zip code and re-enter.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eingabe einer Postleitzahl ist ungültig. Bestätigen Sie die Postleitzahl und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal introducido no es válido. Verifique el código postal y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entrée de code postal invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoer van postcode is ongeldig. Controleer de postcode en voer deze opnieuw in")); }

        // Actions
	};
}



