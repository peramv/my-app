#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_clb_amount_cannot_be_transfered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_clb_amount_cannot_be_transfered() { }
		~CIFast_IFast_ifastcbo_err_clb_amount_cannot_be_transfered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLB_AMOUNT_CANNOT_BE_TRANSFERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CLB Amount cannot be transferred since SIN of from and to beneficiary are different.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de BEC ne peu être transféré puisque les NAS des bénéficiaires source et cible sont différents.")); }

        // Actions
	};
}



