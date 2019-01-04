#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_audit_rec_not_written : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_audit_rec_not_written() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_audit_rec_not_written() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUDIT_REC_NOT_WRITTEN")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Audit record not written.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Audit record not written.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Prüfungseintrag nicht geschrieben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Registro de auditoría no escrito.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement de vérification n'est pas écrit.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Auditrecord is niet geschreven")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verifiez le systeme.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das System")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el sistema")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het systeem")); }
	};
}



