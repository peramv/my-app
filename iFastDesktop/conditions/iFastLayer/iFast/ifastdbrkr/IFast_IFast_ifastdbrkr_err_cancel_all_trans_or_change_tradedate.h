#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancel_all_trans_or_change_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancel_all_trans_or_change_tradedate() { }
		~CIFast_IFast_ifastdbrkr_err_cancel_all_trans_or_change_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCEL_ALL_TRANS_OR_CHANGE_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("BackDate: Cancel all transactions on or after or change tradedate.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("BackDate: Cancel all transactions on or after or change tradedate.")); }

        // Actions
	};
}



