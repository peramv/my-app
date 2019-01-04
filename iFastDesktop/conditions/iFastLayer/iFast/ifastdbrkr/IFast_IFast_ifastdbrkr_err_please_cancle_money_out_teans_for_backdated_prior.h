#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_please_cancle_money_out_teans_for_backdated_prior : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_please_cancle_money_out_teans_for_backdated_prior() { }
		~CIFast_IFast_ifastdbrkr_err_please_cancle_money_out_teans_for_backdated_prior() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PLEASE_CANCLE_MONEY_OUT_TEANS_FOR_BACKDATED_PRIOR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please cancel money out transaction for backdated trade prior to subsequent EUSD money out.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Please cancel money out transaction for backdated trade prior to subsequent EUSD money out.")); }

        // Actions
	};
}



