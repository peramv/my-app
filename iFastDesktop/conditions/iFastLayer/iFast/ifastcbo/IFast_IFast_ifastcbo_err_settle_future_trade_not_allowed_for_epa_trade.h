﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settle_future_trade_not_allowed_for_epa_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settle_future_trade_not_allowed_for_epa_trade() { }
		~CIFast_IFast_ifastcbo_err_settle_future_trade_not_allowed_for_epa_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_FUTURE_TRADE_NOT_ALLOWED_FOR_EPA_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to settle future EPA trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de régler une future transaction APE.")); }

        // Actions
	};
}



