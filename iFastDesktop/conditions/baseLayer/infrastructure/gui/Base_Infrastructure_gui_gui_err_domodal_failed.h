#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_gui_gui_err_domodal_failed : public CConditionObject
	{
	public:
		CBase_Infrastructure_gui_gui_err_domodal_failed() { }
		~CBase_Infrastructure_gui_gui_err_domodal_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_DOMODAL_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("gui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. View Manager request for variable data failed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Field Tag '^'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Die View Manager-Anfrage für variable Daten ist fehlgeschlagen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Etiqueta de campo no válida %FIELD_TAG%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. La demande de données variables du gestionnaire de l'affichage a échoué.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. De aanvraag voor variabele gegevens door View Manager is mislukt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify CBO code.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el código CBO.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



