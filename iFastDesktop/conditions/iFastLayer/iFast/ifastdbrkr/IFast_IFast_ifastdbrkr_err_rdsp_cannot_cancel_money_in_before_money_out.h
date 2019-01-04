#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_money_in_before_money_out : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_money_in_before_money_out() { }
		~CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_money_in_before_money_out() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DBRKR_RDSP_CANNOT_CANCEL_MONEY_IN_BEFORE_MONEY_OUT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot cancel the trade before the Money-out transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cannot cancel the trade before the Money-out transaction.")); }

        // Actions
	};
}



