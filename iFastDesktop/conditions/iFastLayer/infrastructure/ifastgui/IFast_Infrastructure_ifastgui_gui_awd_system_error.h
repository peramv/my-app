#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_awd_system_error : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_awd_system_error() { }
		~CIFast_Infrastructure_ifastgui_gui_awd_system_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_SYSTEM_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%FIELD% must be %LENGTH% characters long.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("^ must be ^ characters long.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%FIELD% muss %LENGTH% Zeichen lang sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%FIELD% debe tener %LENGTH% caracteres.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ doit être composé de %LENGTH% caractères.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%FIELD% moet %LENGTH% tekens lang zijn")); }

        // Actions
	};
}



