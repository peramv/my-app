#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_encorr_ole_error : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_encorr_ole_error() { }
		~CIFast_Infrastructure_ifastgui_gui_encorr_ole_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ENCORR_OLE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem due to a View Manager application disconnection error.  Return Code: %rc%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Field '^' with a maximum length of, '^' characters, has been exceeded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem wegen eines View Manager-Anwendungs-Trennungsfehlers.  Rückgabecode: %rc%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno debido a un error de desconexión de la aplicación de View Manager.  Código de retorno: %rc%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La longueur maximale du champ, qui est de %LENGTH% caractères, a été excédée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld %FIELD% met een maximumlengte van %LENGTH% tekens, is overschreden")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Enter a value of fewer characters in length.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Entrez une valeur composée de moins de caractères.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef een waarde op met minder tekens")); }
	};
}



