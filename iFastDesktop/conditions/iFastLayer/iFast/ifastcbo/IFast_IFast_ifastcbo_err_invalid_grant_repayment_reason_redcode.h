#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_grant_repayment_reason_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_grant_repayment_reason_redcode() { }
		~CIFast_IFast_ifastcbo_err_invalid_grant_repayment_reason_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GRANT_REPAYMENT_REASON_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid grant repayment reason for redemption code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Raison de remboursement de subvention invalide pour le code de rachat")); }

        // Actions
	};
}



