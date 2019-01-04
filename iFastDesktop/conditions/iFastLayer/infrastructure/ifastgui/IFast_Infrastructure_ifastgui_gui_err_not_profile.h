#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_err_not_profile : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_err_not_profile() { }
		~CIFast_Infrastructure_ifastgui_gui_err_not_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_NOT_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is not authorized for this system.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is not authorized for this system.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Operator hat keine Autorisierung für dieses System.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador no está autorizado para este sistema.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Opérateur non autorisé pour ce sytème")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator is niet gemachtigd voor dit systeem")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor, wenn Sie Hilfe zur Operatorsicherheit benötigen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour obtenir une assistance en matière de sécurité de l'opérateur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor voor hulp bij operatorveiligheid")); }
	};
}



