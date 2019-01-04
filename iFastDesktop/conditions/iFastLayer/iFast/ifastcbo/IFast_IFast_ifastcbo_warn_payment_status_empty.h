#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_payment_status_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_payment_status_empty() { }
		~CIFast_IFast_ifastcbo_warn_payment_status_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAYMENT_STATUS_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment Status cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le statut du paiement est requis.")); }

        // Actions
	};
}



