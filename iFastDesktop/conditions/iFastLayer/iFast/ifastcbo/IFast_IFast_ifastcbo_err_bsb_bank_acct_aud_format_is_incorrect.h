#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bsb_bank_acct_aud_format_is_incorrect : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bsb_bank_acct_aud_format_is_incorrect() { }
		~CIFast_IFast_ifastcbo_err_bsb_bank_acct_aud_format_is_incorrect() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BSB_BANK_ACCT_AUD_FORMAT_IS_INCORRECT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number should be a numeric value with length between 6 to 10, as the bank currency is Australia Dollar.")); }
	};
}