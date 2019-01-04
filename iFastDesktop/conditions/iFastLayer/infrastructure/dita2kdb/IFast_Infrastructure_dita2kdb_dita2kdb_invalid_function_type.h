﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_function_type : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_function_type() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_function_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_FUNCTION_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid function type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid function type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Funktionstyp.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Tipo de función no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de fonction invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig functietype")); }

        // Actions
	};
}



