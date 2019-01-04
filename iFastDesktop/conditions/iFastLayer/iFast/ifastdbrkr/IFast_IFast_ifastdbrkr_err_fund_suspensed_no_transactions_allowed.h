#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_suspensed_no_transactions_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_suspensed_no_transactions_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_fund_suspensed_no_transactions_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_SUSPENDED_NO_TRANSACTIONS_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund suspended - no transactions allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonds suspendu - aucune transaction autorisée.")); }

        // Actions
	};
}

