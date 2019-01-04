#pragma once

#include "..\..\..\ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_warn_result_from_browser_screen : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_warn_result_from_browser_screen() { }
		~CIFast_IFast_ifastbp_warn_result_from_browser_screen() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESULT_FROM_BROWSER_SCREEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The error code# %CODE% was returned from browser screen %SCREEN%.")); }

		// Actions
	};
}



