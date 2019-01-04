#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_broker_payment_instructions_for_distribution_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_broker_payment_instructions_for_distribution_missing() { }
		~CIFast_IFast_ifastcbo_warn_broker_payment_instructions_for_distribution_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BROKER_PAYMENT_INSTRUCTIONS_FOR_DISTRIBUTION_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Broker payment instructions for distribution missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions de paiement du courtier pour la distribution sont manquantes.")); }

        // Actions
	};
}



