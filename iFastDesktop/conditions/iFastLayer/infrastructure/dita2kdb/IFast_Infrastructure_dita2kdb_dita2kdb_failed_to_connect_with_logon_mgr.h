#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_failed_to_connect_with_logon_mgr : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_failed_to_connect_with_logon_mgr() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_failed_to_connect_with_logon_mgr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_FAILED_TO_CONNECT_WITH_LOGON_MGR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Failed to connect with the Logon Manager")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Failed to connect with the Logon Manager")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verbindung mit dem Anmelde-Manager fehlgeschlagen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no se pudo conectar con el Logon Manager")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de connexion au gestionnaire d'ouverture de session.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbinding met aanmeldingsmanager is mislukt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich zwecks Überprüfung der Installation von TaLogon an einen Supervisor")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor to verify the installation of TaLogon")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour vérifier l'installation de ?")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor om de installatie van TaLogon te controleren")); }
	};
}



