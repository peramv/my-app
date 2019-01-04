#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_parse_idi_missing_value : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_parse_idi_missing_value() { }
		~CIFast_Infrastructure_dicore_dicore_parse_idi_missing_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PARSE_IDI_MISSING_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A required IDI string separator is missing after %TAG_NAME%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("A required IDI string separator is missing after %TAG_NAME%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein erforderliches IDI-String-Trennzeichen fehlt nach %TAG_NAME%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta un separador de cadena IDI obligatorio después de %TAG_NAME%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un séparateur de chaîne IDI requis est manquant après %TAG_NAME%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een vereist scheidingsteken voor de IDI-string ontbreekt na %TAG_NAME%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Add the separator after the IDI value.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Add the separator after the IDI value.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Fügen Sie das Trennzeichen hinter dem IDI-Wert ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Añada el separador después del valor IDI.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ajoutez le séparateur après la valeur IDI.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Voeg het scheidingsteken toe na de IDI-waarde")); }
	};
}



