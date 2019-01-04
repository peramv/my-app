#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_no_divtype_unit_rate_exists_for_this_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_no_divtype_unit_rate_exists_for_this_date() { }
		~CIFast_IFast_ifastcbo_warn_no_divtype_unit_rate_exists_for_this_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NO_DIVTYPE_UNIT_RATE_EXISTS_FOR_THIS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No %DIVTYPE% unit rate exists for this date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("No %DIVTYPE% unit rate exists for this date.")); }

        // Actions
	};
}



