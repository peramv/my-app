#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_country_of_issue_is_required_for_business_number_and_trust_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_country_of_issue_is_required_for_business_number_and_trust_number() { }
		~CIFast_IFast_ifastcbo_warn_country_of_issue_is_required_for_business_number_and_trust_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_COUNTRY_OF_ISSUE_IS_REQUIRED_FOR_BUSINESS_NUMBER_AND_TRUST_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of Issue is required for Business Number and Trust Number")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check country of issue of ID.")); }
	};
}



