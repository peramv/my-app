#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_sts_error : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_sts_error() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_sts_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_STS_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("STS error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("STS error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("STS-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de STS.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur STS")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("STS-fout")); }

        // Actions
	};
}



