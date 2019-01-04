#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_no_systems : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_no_systems() { }
		~CIFast_IFast_dita2kdb_dita2kdb_no_systems() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_NO_SYSTEMS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid Shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Aktionär")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Accionista no válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Actionnaire invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige aandeelhouder")); }

        // Actions
	};
}



