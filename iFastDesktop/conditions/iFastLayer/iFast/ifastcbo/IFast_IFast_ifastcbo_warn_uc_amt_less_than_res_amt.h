#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_uc_amt_less_than_res_amt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_uc_amt_less_than_res_amt() { }
		~CIFast_IFast_ifastcbo_warn_uc_amt_less_than_res_amt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_UC_AMT_LESS_THAN_RES_AMT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unassisted Balance $%UC_AMT% is less than Residual Unassisted $%RES_AMT%.")); }

        // Actions
	};
}



