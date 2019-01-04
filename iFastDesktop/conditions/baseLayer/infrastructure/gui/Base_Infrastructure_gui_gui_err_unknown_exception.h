#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_gui_gui_err_unknown_exception : public CConditionObject
	{
	public:
		CBase_Infrastructure_gui_gui_err_unknown_exception() { }
		~CBase_Infrastructure_gui_gui_err_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("gui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this password.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Kennwort nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("^'")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce mot de passe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("^'")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify password and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Kennwort und geben Sie es erneut ein.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le mot de passe et réessayez.")); }
	};
}



