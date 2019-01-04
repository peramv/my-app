#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_yield_date : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_yield_date() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_yield_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_YIELD_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No interest accrual information available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No interest accrual information available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Stückzinsen-Informationen verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información disponible sobre los intereses devengados")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur les intérêts courus n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen gegevens over rentegroei beschikbaar")); }

        // Actions
	};
}



