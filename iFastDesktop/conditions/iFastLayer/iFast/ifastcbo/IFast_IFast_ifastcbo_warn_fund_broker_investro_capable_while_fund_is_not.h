#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_broker_investro_capable_while_fund_is_not : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_broker_investro_capable_while_fund_is_not() { }
		~CIFast_IFast_ifastcbo_warn_fund_broker_investro_capable_while_fund_is_not() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_BROKER_INVESTRO_CAPABLE_WHILE_FUND_IS_NOT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund broker %fundbroker% is Investro capable, while fund %fund% is not.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund broker %fundbroker% is Investro capable, while fund %fund% is not.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier en fonds %fundbroker% supporte Investro, mais le fonds %fund% ne le supporte pas.")); }

        // Actions
	};
}



