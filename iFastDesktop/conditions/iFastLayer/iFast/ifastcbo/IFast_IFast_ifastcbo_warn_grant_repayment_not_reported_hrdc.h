#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_grant_repayment_not_reported_hrdc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_grant_repayment_not_reported_hrdc() { }
		~CIFast_IFast_ifastcbo_warn_grant_repayment_not_reported_hrdc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_GRANT_REPAYMENT_NOT_REPORTED_HRDC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This grant repayment will not be reported to HRDC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le remboursement de subvention ne sera pas déclaré au DRHC.")); }

        // Actions
	};
}



