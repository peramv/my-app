#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_record_already_exist : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_record_already_exist() { }
		~CBase_Ifds_dita2kdb_dita2kdb_record_already_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_RECORD_ALREADY_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Error occured converting a multi-byte string to a unicode string.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error occured converting a multi-byte string to a unicode string.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Error occured converting a multi-byte string to a unicode string.")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



