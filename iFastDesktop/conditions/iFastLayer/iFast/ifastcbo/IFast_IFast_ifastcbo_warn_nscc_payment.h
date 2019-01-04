#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_nscc_payment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_nscc_payment() { }
		~CIFast_IFast_ifastcbo_warn_nscc_payment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NSCC_PAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("NSCC Broker payment can be made via NSCC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paiement du courtier NSCC peut être fait par NSCC.")); }

        // Actions
	};
}



