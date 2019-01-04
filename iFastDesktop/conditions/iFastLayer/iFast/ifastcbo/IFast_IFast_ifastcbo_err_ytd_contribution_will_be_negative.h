#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ytd_contribution_will_be_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ytd_contribution_will_be_negative() { }
		~CIFast_IFast_ifastcbo_err_ytd_contribution_will_be_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_YTD_CONTRIBUTION_WILL_BE_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This transaction will reduce the YTD contribution to negative.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette transaction rendra la cotisation à ce jour négative.")); }

        // Actions
	};
}



