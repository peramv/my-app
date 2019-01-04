#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_invalid_batch_num : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_invalid_batch_num() { }
		~CIFast_IFast_dita2kdb_dita2kdb_invalid_batch_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_BATCH_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account number is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer ist ungültig")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El número de cuenta no es válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro de compte invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer is ongeldig")); }

        // Actions
	};
}



