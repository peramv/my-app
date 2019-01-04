#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_audit_file_bad_open : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_audit_file_bad_open() { }
		~CIFast_IFast_dita2kdb_dita2kdb_audit_file_bad_open() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_AUDIT_FILE_BAD_OPEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Joint information is available only for joint accounts.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Joint information is available only for joint accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Gemeinschaftsinformationen sind nur für Gemeinschaftskonten erhältlich")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La información conjunta sólo está disponible para cuentas conjuntas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information conjointe n'est disponible que pour les comptes conjoints.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gezamenlijke gegevens zijn alleen beschikbaar voor gezamenlijke accounts")); }

        // Actions
	};
}



