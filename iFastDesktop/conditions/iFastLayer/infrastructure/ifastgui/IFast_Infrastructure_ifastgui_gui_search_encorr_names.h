#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_search_encorr_names : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_search_encorr_names() { }
		~CIFast_Infrastructure_ifastgui_gui_search_encorr_names() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_ENCORR_NAMES")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem due to a View Manager application connection error.  Return Code: %rc%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem due to a View Manager application connection error.  Return Code: %rc%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem wegen eines View Manager-Anwendungs-Verbindungsfehlers.  Rückgabecode: %rc%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno debido a un error de conexión con la aplicación de View Manager.  Código de retorno: %rc%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne dû à une erreur de connexion à l'application du gestionnaire de l'affichage. Code de renvoi : %rc%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat er een fout is opgetreden bij het aansluiten van de View Manager-toepassing.  Retourcode: %rc%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



