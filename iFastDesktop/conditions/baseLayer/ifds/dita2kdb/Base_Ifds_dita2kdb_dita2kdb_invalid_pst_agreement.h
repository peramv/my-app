#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_pst_agreement : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_pst_agreement() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_pst_agreement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_PST_AGREEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Host connection manager not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Host connection manager not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennwort verweigert – Altes Kennwort nicht korrekt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el administrador de la conexión con el host.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'exploitant de connexion de l'hôte est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Verbindingsmanager host is niet gevonden.")); }

        // Actions
	};
}



