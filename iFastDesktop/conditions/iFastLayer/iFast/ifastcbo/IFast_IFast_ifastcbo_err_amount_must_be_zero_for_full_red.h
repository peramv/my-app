#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_must_be_zero_for_full_red : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_must_be_zero_for_full_red() { }
		~CIFast_IFast_ifastcbo_err_amount_must_be_zero_for_full_red() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_MUST_BE_ZERO_FOR_FULL_RED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount must be zero and amount type must be 'Amount' for Full Redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount must be zero and amount type must be 'Amount' for Full Redemption.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Amount must be zero and amount type must be 'Amount' for Full Redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour le rachat total, le montant doit être de zéro et le type de montant doit être Montant.")); }

        // Actions
	};
}



