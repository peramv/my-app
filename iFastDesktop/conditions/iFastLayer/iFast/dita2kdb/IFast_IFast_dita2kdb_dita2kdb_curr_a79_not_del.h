#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_curr_a79_not_del : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_curr_a79_not_del() { }
		~CIFast_IFast_dita2kdb_dita2kdb_curr_a79_not_del() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_CURR_A79_NOT_DEL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("As of date was not entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("As of date was not entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("“Mit Wirkung vom…”-Datum war nicht eingetragen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo la fecha Hasta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette date n'a pas été saisie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vanaf-datum is niet ingevoerd")); }

        // Actions
	};
}



