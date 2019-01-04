#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_broker_payment_for_setup_not_in_pair : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_broker_payment_for_setup_not_in_pair() { }
		~CIFast_IFast_ifastcbo_warn_broker_payment_for_setup_not_in_pair() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BROKER_PAYMENT_FOR_SETUP_NOT_IN_PAIR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment for both Redemption and Distribution must be setup in pair")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paiement du rachat et de la distribution doit être réglé en paire.")); }

        // Actions
	};
}



