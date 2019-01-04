#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_no_password_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_no_password_entered() { }
		~CIFast_IFast_ifastgui_gui_no_password_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_PASSWORD_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No password entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucun mot de passe n'a ete saisi")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Kennwort eingegeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo la contraseña")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun mot de passe n'a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen wachtwoord opgegeven")); }

        // Actions
	};
}



