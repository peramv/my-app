#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_encorr_already_active : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_encorr_already_active() { }
		~CIFast_Infrastructure_ifastgui_gui_encorr_already_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ENCORR_ALREADY_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Method %METHOD% should never be called.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem due to a View Manager request error.  Message: %msg%  Return Code: %rc%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem wegen eines View Manager-Anfragefehlers.  Meldung: %msg% Rückgabecode: %rc%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El método %METHOD% no debe llamarse nunca.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne dû à une erreur de demande du gestionnaire de l'affichage. Message : %msg%, code de renvoi : %rc%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Methode %METHOD% mag nooit worden aangeroepen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de CBO-code")); }
	};
}



