#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_s0_master_not_found : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_s0_master_not_found() { }
		~CBase_Ifds_dita2kdb_dita2kdb_s0_master_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_S0_MASTER_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("File Response Buffer is malformed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaktion nicht gefunden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("File Response Buffer is malformed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tampon de réponse du fichier est incorrect.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("File Response Buffer is malformed.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



