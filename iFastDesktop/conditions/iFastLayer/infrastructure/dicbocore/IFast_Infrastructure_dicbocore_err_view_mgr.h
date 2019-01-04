#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_view_mgr : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_view_mgr() { }
		~CIFast_Infrastructure_dicbocore_err_view_mgr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VIEW_MGR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. View Manager received an error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. View Manager received an error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Fehler im View Manager.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. View Manager recibió un error.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le gestionnaire de l'affichage a reçu une erreur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. ViewManager heeft een fout ontvangen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



