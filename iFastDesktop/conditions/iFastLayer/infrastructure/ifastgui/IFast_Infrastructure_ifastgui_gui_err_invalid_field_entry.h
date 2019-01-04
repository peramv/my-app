#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_err_invalid_field_entry : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_err_invalid_field_entry() { }
		~CIFast_Infrastructure_ifastgui_gui_err_invalid_field_entry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_INVALID_FIELD_ENTRY")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is not signed on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is not signed on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Operator ist nicht angemeldet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador no se ha identificado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'opérateur n'a aucune session ouverte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator heeft zich niet aangemeld")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Sign on before calling this function.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Sign on before calling this function.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Melden Sie sich an, bevor Sie diese Funktion aufrufen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Sign on before calling this function.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ouvrez une session avant de faire appel à cette fonction.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld u aan voordat u deze functie aanroept")); }
	};
}



