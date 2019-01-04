#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_payment_status_is_outstanding : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_payment_status_is_outstanding() { }
		~CIFast_IFast_ifastcbo_err_payment_status_is_outstanding() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYMENT_STATUS_IS_OUTSTANDING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The trade will not be priced with Payment Status as ‘Payment Outstanding’.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction ne sera pas évaluée si le statut de paiement est Paiement non réglé.")); }

        // Actions
	};
}



