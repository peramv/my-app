#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transaction_cannot_be_cancelled_before_night_run : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transaction_cannot_be_cancelled_before_night_run() { }
		~CIFast_IFast_ifastdbrkr_err_transaction_cannot_be_cancelled_before_night_run() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_CANNOT_BE_CANCELLED_BEFORE_NIGHT_RUN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction cannot be cancelled before night run.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction ne peut pas être annulée avant le lendemain.")); }

        // Actions
	};
}



