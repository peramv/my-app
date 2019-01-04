﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_invalid_repayment_reason : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_invalid_repayment_reason() { }
		~CIFast_IFast_ifastcbo_err_rdsp_invalid_repayment_reason() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_INVALID_REPAYMENT_REASON")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Repayment Reason.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Invalid Repayment Reason.")); }

        // Actions
	};
}



