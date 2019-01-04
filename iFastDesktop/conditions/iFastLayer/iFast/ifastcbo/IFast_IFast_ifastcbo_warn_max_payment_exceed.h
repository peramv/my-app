#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_max_payment_exceed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_max_payment_exceed() { }
		~CIFast_IFast_ifastcbo_warn_max_payment_exceed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_MAX_PAYMENT_EXCEED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maximum Payout Amount has exceeded.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maximum Payout Amount has exceeded.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Maximum Payout Amount has exceeded.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de versement maximal est excédé.")); }

        // Actions
	};
}



