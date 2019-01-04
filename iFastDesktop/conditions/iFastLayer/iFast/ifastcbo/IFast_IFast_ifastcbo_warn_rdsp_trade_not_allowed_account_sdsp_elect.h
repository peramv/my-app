#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_trade_not_allowed_account_sdsp_elect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_trade_not_allowed_account_sdsp_elect() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_trade_not_allowed_account_sdsp_elect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_TRADE_NOT_ALLOWED_ACCOUNT_SDSP_ELECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade not allowed for a RDSP account SDSP elect.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Trade not allowed for a RDSP account SDSP elect.")); }

        // Actions
	};
}



