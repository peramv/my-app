#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicore_dicore_ipc_synch_fail : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicore_dicore_ipc_synch_fail() { }
		~CBase_Infrastructure_dicore_dicore_ipc_synch_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_IPC_SYNCH_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("IPCClient/IPCServer synchronization error. %GENERIC%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("IPCClient/IPCServer synchronization error. %GENERIC%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("IPCClient/IPCServer-Synchronisationsfehler. %GENERIC%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de sincronización IPCCliente/IPCServidor. %GENERIC%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de synchronisation du serveur IPC/du client IPC. %GENERIC%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Synchronisatiefout IPC-client/IPC-server %GENERIC%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Reestablish connection.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Reestablish connection.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Stellen Sie die Verbindung erneut her.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Reestablish connection.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Rétablissez la connexion.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Maak opnieuw verbinding")); }
	};
}



