#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_error : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_error() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_duplicate_key_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_DUPLICATE_KEY_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD Work has no data.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD Work has no data.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Arbeit hat kein Datum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tarea de AWD no tiene datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le travail AWD ne contient aucune donnée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-werk heeft geen gegevens")); }

        // Actions
	};
}



