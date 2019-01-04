#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fund_investro_capable_while_fund_broker_is_not : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fund_investro_capable_while_fund_broker_is_not() { }
		~CIFast_IFast_ifastcbo_warn_fund_investro_capable_while_fund_broker_is_not() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FUND_INVESTRO_CAPABLE_WHILE_FUND_BROKER_IS_NOT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %fund% is Investro capable, while fundbroker %fundbroker% is not.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %fund% is Investro capable, while fundbroker %fundbroker% is not.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %fund% supporte Investro, mais le courtier en fonds %fundbroker% ne le supporte pas.")); }

        // Actions
	};
}



