#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_transaction_awaiting_hrsdc_response_cannot_change_allocations : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_transaction_awaiting_hrsdc_response_cannot_change_allocations() { }
		~CIFast_IFast_ifastcbo_err_transaction_awaiting_hrsdc_response_cannot_change_allocations() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_AWAITING_HRSDC_RESPONSE_CANNOT_CHANGE_ALLOCATIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction is awaiting a response from HRSDC hence cannot change allocations.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction est en attente d'une réponse de RHDCC, les allocations ne peuvent être modifiées.")); }


        // Actions
	};
}



