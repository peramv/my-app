#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cntry_of_issue_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cntry_of_issue_is_blank() { }
		~CIFast_IFast_ifastcbo_warn_cntry_of_issue_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CNTRY_OF_ISSUE_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of issue is blank.")); }

        // Actions
	};
}



