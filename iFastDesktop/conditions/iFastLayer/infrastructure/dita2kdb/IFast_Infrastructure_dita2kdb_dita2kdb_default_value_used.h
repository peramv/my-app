#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_default_value_used : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_default_value_used() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_default_value_used() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_DEFAULT_VALUE_USED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default value used.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Default value used.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Standardwert wurde verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se utilizó el valor predeterminado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur par défaut utilisée")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Standaardwaarde is gebruikt")); }

        // Actions
	};
}



