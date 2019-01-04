﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_invalid_monthly_accum : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_invalid_monthly_accum() { }
		~CBase_Ifds_dita2kdb_dita2kdb_invalid_monthly_accum() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_MONTHLY_ACCUM")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Please select a broker first.")); }

        // Actions
	};
}



