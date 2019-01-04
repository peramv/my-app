#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_invalid_time : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_invalid_time() { }
		~CBase_Ifds_dicbocore_err_invalid_time() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TIME")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dev")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dev")); }

        // Actions
	};
}



