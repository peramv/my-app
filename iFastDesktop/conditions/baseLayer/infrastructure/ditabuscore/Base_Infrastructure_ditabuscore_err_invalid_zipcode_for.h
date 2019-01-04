#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_invalid_zipcode_for : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_invalid_zipcode_for() { }
		~CBase_Infrastructure_ditabuscore_err_invalid_zipcode_for() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_ZIPCODE_FOR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entry of zip code is invalid for %FIELD%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entry of zip code is invalid for ^. Verify zip code and re-enter.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Eingabe einer Postleitzahl für %FIELD% ist ungültig. Bestätigen Sie die Postleitzahl und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código postal introducido no es válido para %FIELD%. Verifique el código postal y vuelva a introducirlo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La saisie de code postal est invalide pour le champ %FIELD%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Invoer postcode is ongeldig voor %FIELD%. Controleer de postcode en voer deze opnieuw in")); }

        // Actions
	};
}



