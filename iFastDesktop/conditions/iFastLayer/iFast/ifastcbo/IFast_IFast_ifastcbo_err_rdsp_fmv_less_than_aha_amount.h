#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_fmv_less_than_aha_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_fmv_less_than_aha_amount() { }
		~CIFast_IFast_ifastcbo_err_rdsp_fmv_less_than_aha_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_FMV_LESS_THAN_AHA_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("FMV is less than AHA amount, payment may be rejected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("FMV is less than AHA amount, payment may be rejected.")); }

        // Actions
	};
}



