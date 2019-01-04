#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_err_dialog_create_failed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_err_dialog_create_failed() { }
		~CIFast_Infrastructure_ifastgui_gui_err_dialog_create_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_DIALOG_CREATE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to read data file SIGNON2.DAT")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to retrieve data for '^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datei SIGNON2.DAT kann nicht geöffnet werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible recuperar los datos para %LABEL%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de lire le fichier de données SIGNON2.DAT.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevens voor %LABEL% konden niet worden opgehaald")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



