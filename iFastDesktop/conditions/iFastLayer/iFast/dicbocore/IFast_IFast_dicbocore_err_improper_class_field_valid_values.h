#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_improper_class_field_valid_values : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_improper_class_field_valid_values() { }
		~CIFast_IFast_dicbocore_err_improper_class_field_valid_values() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IMPROPER_CLASS_FIELD_VALID_VALUES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not active as of the input effective date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le compte n'est pas actif a compter de la date d'effet saisie. Veuillez ressaisir.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto ist nicht aktiv ab dem eingegebenen Effektivdatum. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no está activa a la fecha de entrada en vigencia de entrada. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas actif à partir de la date d'entrée en vigueur saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is niet actief vanaf de ingevoerde ingangsdatum. Vul opnieuw in")); }

        // Actions
	};
}



