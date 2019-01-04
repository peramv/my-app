#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_invalid_payment_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_invalid_payment_type() { }
		~CIFast_IFast_ifastdbrkr_err_acct_level_ia_record_invalid_payment_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_LEVEL_IA_RECORD_INVALID_PAYMENT_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid payment type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de paiement invalide")); }

        // Actions
	};
}



