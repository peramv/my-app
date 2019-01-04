#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicbocore_err_view_mgr : public CConditionObject
	{
	public:
		CBase_Ifds_dicbocore_err_view_mgr() { }
		~CBase_Ifds_dicbocore_err_view_mgr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_VIEW_MGR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Dev")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dev")); }

        // Actions
	};
}



