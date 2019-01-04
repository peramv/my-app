#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_missing_dd_card : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_missing_dd_card() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_missing_dd_card() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_MISSING_DD_CARD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation information must be entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Allocation information must be entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zuweisungs-Information muss eingegeben werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse la información de asignación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information sur la répartition est requise.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moeten allocatiegegevens worden ingevoerd")); }

        // Actions
	};
}



