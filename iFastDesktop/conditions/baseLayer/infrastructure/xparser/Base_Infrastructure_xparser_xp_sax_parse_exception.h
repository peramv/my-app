#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_xparser_xp_sax_parse_exception : public CConditionObject
	{
	public:
		CBase_Infrastructure_xparser_xp_sax_parse_exception() { }
		~CBase_Infrastructure_xparser_xp_sax_parse_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("XP_SAX_PARSE_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Number specified, %INDEX%, is out of range.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Number specified, '^', is out of range.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die festgelegte Anzahl %INDEX% liegt außerhalb des Bereichs.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número especificado, %INDEX%, está fuera de rango.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro spécifié, %INDEX%, est hors plage.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Opgegeven nummer, %INDEX%, ligt buiten het bereik")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Make sure the number is correct.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Make sure the number is correct.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Vergewissern Sie sich, dass es sich um die richtige Nummer handelt.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique que el número sea correcto.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Assurez-vous que le numéro est exact.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Zorg ervoor dat het juiste nummer is gebruikt")); }
	};
}



