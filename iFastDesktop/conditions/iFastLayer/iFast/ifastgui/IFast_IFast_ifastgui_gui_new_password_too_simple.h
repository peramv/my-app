#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_new_password_too_simple : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_new_password_too_simple() { }
		~CIFast_IFast_ifastgui_gui_new_password_too_simple() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NEW_PASSWORD_TOO_SIMPLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The new password must contain at least %NUM_CHARS% characters.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nouveau mot de passe doit être composé d'au moins %NUM_CHARS% caractères.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try a new password")); }
	};
}



