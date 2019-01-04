#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pending_or_unsettled_trade_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pending_or_unsettled_trade_exists() { }
		~CIFast_IFast_ifastcbo_warn_pending_or_unsettled_trade_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PENDING_OR_UNSETTLED_TRADE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pending or unsettled trade exists, Initial Next Draw Date cannot be changed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une transaction PAC en suspend ou non réglée est présente, la Prochaine date de contrôle ne peut pas être modifiée.")); }

        // Actions
	};
}



