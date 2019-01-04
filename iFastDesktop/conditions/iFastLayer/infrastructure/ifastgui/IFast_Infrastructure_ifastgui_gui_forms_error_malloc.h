#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_forms_error_malloc : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_forms_error_malloc() { }
		~CIFast_Infrastructure_ifastgui_gui_forms_error_malloc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_FORMS_ERROR_MALLOC")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because a view request failed. Primary RC: %prim%  Secondary RC: %sec%  Error Message: %error%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because a view request failed. Primary RC: %prim%  Secondary RC: %sec%  Error Message: %error%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem, da eine Transaktions-Anfrage fehlgeschlagen ist. Primärer Rückgabecode: %prim% Sekundärer RC: %sec% Fehlermeldung: %error%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque falló una solicitud de view. RC principal: %prim%  RC secundaria: %sec%  Mensaje de error: %error%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne parce qu'une demande d'affichage a échoué. Enregistrement principal : %prim%, enregistrement secondaire : %sec%, message d'erreur : %error%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat een transactieopdracht is mislukt. Primaire retourcode: %prim%  Secundaire retourcode: %sec%  Foutbericht: %error%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



