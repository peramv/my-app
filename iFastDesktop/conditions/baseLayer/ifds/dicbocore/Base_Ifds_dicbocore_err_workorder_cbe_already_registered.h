#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_workorder_cbe_already_registered : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_workorder_cbe_already_registered() { }
		~CBase_Ifds_dicbocore_err_workorder_cbe_already_registered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WORKORDER_CBE_ALREADY_REGISTERED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dev")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dev")); }

        // Actions
	};
}



