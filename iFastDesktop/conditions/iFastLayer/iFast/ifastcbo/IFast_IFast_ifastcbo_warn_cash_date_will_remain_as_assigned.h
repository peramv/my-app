#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cash_date_will_remain_as_assigned : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cash_date_will_remain_as_assigned() { }
		~CIFast_IFast_ifastcbo_warn_cash_date_will_remain_as_assigned() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CASH_DATE_WILL_REMAIN_AS_ASSIGNED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please note cash date will remain as assigned.")); }		
		virtual DString GetMessage_FR_CA() const { return DString(I_("Please note cash date will remain as assigned.")); }		

        // Actions
	};
}



