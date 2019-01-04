#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_batc : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_batc() { }
		~CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_batc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_WRAPUP_ERR_MUST_ENTER_BATC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is disabled.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is disabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Operator ist gesperrt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador está inhabilitado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Opérateur désactivé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator is niet actief")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor, um die Operator-ID zu aktivieren.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour activer le code d'opérateur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor om het operator-ID te activeren")); }
	};
}



