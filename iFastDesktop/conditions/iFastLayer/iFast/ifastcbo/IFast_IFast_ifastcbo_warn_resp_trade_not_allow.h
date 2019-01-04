#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_trade_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_trade_not_allow() { }
		~CIFast_IFast_ifastcbo_warn_resp_trade_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_TRADE_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RESP/Family RESP trading is not supported.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les opérations REEE/REEE familial ne sont pas supportées.")); }

        // Actions
	};
}



