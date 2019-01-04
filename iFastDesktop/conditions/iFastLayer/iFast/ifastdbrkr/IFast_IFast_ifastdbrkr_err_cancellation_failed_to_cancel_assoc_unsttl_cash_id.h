#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancellation_failed_to_cancel_assoc_unsttl_cash_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancellation_failed_to_cancel_assoc_unsttl_cash_id() { }
		~CIFast_IFast_ifastdbrkr_err_cancellation_failed_to_cancel_assoc_unsttl_cash_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCELLATION_FAILED_TO_CANCEL_ASSOC_UNSTTL_CASH_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to cancel associated unsettled cash ID!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'annuler la distribution de revenu comptant non réglée associée!")); }

        // Actions
	};
}



