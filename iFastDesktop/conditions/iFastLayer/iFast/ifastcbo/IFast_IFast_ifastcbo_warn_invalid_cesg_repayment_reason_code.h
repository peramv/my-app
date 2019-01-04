#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_cesg_repayment_reason_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_cesg_repayment_reason_code() { }
		~CIFast_IFast_ifastcbo_warn_invalid_cesg_repayment_reason_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_CESG_REPAYMENT_REASON_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid repayment reason code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de raison de remboursement invalide")); }

        // Actions
	};
}



