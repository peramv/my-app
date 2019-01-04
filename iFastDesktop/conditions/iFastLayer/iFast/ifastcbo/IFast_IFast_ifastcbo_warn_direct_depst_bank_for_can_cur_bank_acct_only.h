#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_direct_depst_bank_for_can_cur_bank_acct_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_direct_depst_bank_for_can_cur_bank_acct_only() { }
		~CIFast_IFast_ifastcbo_warn_direct_depst_bank_for_can_cur_bank_acct_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DIRECT_DEPST_BANK_FOR_CAN_CUR_BANK_ACCT_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Banking is applied only to Canadian Dollar Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire du TEF par dépôt direct n'est applicable qu'aux fonds en dollars canadiens.")); }

        // Actions
	};
}



