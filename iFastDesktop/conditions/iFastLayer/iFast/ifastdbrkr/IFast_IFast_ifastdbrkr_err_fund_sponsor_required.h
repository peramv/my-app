#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_fund_sponsor_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_fund_sponsor_required() { }
		~CIFast_IFast_ifastdbrkr_err_fund_sponsor_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_SPONSOR_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Sponsor is required for BankingEntity 05.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund Sponsor is required for BankingEntity 05.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le promoteur de fonds est requis pour l'entité bancaire 05.")); }

        // Actions
	};
}



