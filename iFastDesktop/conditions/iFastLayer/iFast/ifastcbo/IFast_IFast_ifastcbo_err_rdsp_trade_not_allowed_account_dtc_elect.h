#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_trade_not_allowed_account_dtc_elect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_trade_not_allowed_account_dtc_elect() { }
		~CIFast_IFast_ifastcbo_err_rdsp_trade_not_allowed_account_dtc_elect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_DTC_ELECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade not allowed for a RDSP account DTC elect.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trade not allowed for a RDSP account DTC elect.")); }

        // Actions
	};
}



