#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_value_between_0_and_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_value_between_0_and_100() { }
		~CIFast_IFast_ifastcbo_err_value_between_0_and_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VALUE_BETWEEN_0_AND_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Percentage value must be between 0 and 100.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La valeur saisie doit être comprise entre zéro et cent. Veuillez ressaisir une valeur.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der eingegebene Wert muss zwischen Null und Hundert liegen. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor introducido debe encontrarse entre cero y cien. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de pourcentage doit être située entre 0 et 100.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De opgegeven waarde moet tussen nul en honderd liggen. Vul opnieuw in")); }

        // Actions
	};
}



