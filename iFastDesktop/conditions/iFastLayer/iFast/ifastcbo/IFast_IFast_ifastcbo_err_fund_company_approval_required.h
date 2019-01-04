#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_company_available_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_company_available_required() { }
		~CIFast_IFast_ifastcbo_err_fund_company_available_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_COMPANY_APPROVAL_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Company Approval required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fund Company Approval required.")); }

        // Actions
	};
}



