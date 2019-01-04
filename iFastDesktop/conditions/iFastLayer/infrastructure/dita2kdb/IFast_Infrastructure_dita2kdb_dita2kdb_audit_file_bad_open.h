#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_audit_file_bad_open : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_audit_file_bad_open() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_audit_file_bad_open() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUDIT_FILE_BAD_OPEN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Audit file bad open.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Audit file bad open.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prüfungsdatei nicht richtig geöffnet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Archivo de auditoría no válido abierto.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le dossier de vérification s'est mal ouvert.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Auditbestand is niet goed geopend")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



