#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_sibling_only_blank_or_no : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_sibling_only_blank_or_no() { }
		~CIFast_IFast_ifastcbo_warn_sibling_only_blank_or_no() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SIBLING_ONLY_BLANK_OR_NO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("If No or blank, Additional Grant, CLB and P-Grant will not be applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("S'ils sont réglés à Non ou laissés vides, la subvention supplémentaire, le BEC et la subvention provinciale ne seront pas applicables.")); }

        // Actions
	};
}



