#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_repayment_reason_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_repayment_reason_mandatory() { }
		~CIFast_IFast_ifastcbo_err_rdsp_repayment_reason_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_REPAYMENT_REASON_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Repayment reason must be specified on RDSP withdrawal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Repayment reason must be specified on RDSP withdrawal.")); }

        // Actions
	};
}



