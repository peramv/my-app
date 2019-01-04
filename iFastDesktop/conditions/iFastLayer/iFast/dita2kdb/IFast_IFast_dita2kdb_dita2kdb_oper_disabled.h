#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_oper_disabled : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_oper_disabled() { }
		~CIFast_IFast_dita2kdb_dita2kdb_oper_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_OPER_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No batch number was entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No batch number was entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurde keine Batch-Nummer eingegeben.  Geben Sie eine Batch-Nummer ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo un número de lote. Escriba un número de lote.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun numéro de lot n'a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen batchnummer opgegeven. Typ een batchnummer")); }

        // Actions
	};
}



