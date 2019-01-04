#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trade_is_a_grant : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trade_is_a_grant() { }
		~CIFast_IFast_ifastcbo_warn_trade_is_a_grant() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRADE_IS_A_GRANT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade is a grant.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction est une subvention.")); }

        // Actions
	};
}



