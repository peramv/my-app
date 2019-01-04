#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_audit_rec_not_written : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_audit_rec_not_written() { }
		~CIFast_IFast_dita2kdb_dita2kdb_audit_rec_not_written() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUDIT_REC_NOT_WRITTEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending trade not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Pending trade not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Schwebender Handel nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la operación pendiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transaction en suspens introuvable")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("In behandeling zijnde handel is niet gevonden")); }

        // Actions
	};
}



