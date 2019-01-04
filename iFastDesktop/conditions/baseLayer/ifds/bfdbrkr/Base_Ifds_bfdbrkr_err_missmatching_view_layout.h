#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_bfdbrkr_err_missmatching_view_layout : public CConditionObject
	{
	public:
		CBase_Ifds_bfdbrkr_err_missmatching_view_layout() { }
		~CBase_Ifds_bfdbrkr_err_missmatching_view_layout() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("MISSMATCHING_VIEW_LAYOUT")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("bfdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Missmatching view layout: %VIEW_ID%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please use the correct Desktop version.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please use the correct Desktop version.")); }
	};
}



