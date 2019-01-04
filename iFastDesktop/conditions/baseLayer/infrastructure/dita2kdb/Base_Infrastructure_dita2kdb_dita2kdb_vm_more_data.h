#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_vm_more_data : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_vm_more_data() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_vm_more_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_VM_MORE_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("More data is available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("More data is available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Weitere Daten stehen zur Verfügung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay más datos disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plus de données sont disponibles.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn meer gegevens beschikbaar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("This is not an error.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("This is not an error.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Dies ist kein Fehler.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("This is not an error.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ceci n'est pas une erreur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Dit is geen fout")); }
	};
}



