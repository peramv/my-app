#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_err_profile_selection_failed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_err_profile_selection_failed() { }
		~CIFast_Infrastructure_ifastgui_gui_err_profile_selection_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_PROFILE_SELECTION_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system could not recognize this operator ID.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system could not recognize this operator ID.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System hat die Identität des Operators nicht erkannt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no pudo reconocer la identificación de este operador.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système n'a pas pu reconnaître ce code d'opérateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem heeft dit operator-ID niet herkend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Operator-ID und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify operator ID and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code d'opérateur et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de operator-ID en voer deze opnieuw in")); }
	};
}



