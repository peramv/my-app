#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_bfdbrkr_err_host_connection_mgr_not_found : public CConditionObject
	{
	public:
		CBase_Infrastructure_bfdbrkr_err_host_connection_mgr_not_found() { }
		~CBase_Infrastructure_bfdbrkr_err_host_connection_mgr_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HOST_CONNECTION_MGR_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid post-agreement.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid post-agreement.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.\n\nFehler beim Laden der Funktion. Modul: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.\n\nError al cargar la función. Módulo: %AWD_ERROR_MESSAGE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Postaccord invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.\n\nFout bij laden van functie. Module: %AWD_ERROR_MESSAGE%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify entry. If entry is correct, contact a client service representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la saisie. Si elle est correcte, communiquez avec un représentant du service à la clientèle et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



