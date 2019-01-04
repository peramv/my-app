#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_improper_class_field_valid_values : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_improper_class_field_valid_values() { }
		~CIFast_Infrastructure_dicbocore_err_improper_class_field_valid_values() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IMPROPER_CLASS_FIELD_VALID_VALUES")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Verify the valid values within the .hpp file.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Verify the valid values within the .hpp file.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Bestätigen Sie die gültigen Werte in der .hpp-Datei.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Verifique los valores válidos dentro del archivo .hpp.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Vérifiez les valeurs valides dans le fichier .hpp.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Controleer de geldige waarden in het .hpp-bestand")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



