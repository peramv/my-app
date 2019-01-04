#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_refund_of_special_taxes_exceed_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_refund_of_special_taxes_exceed_redemption() { }
		~CIFast_IFast_ifastcbo_err_refund_of_special_taxes_exceed_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REFUND_OF_SPECIAL_TAXES_EXCEED_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax refund exceeds special tax redemption amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Remboursement d'impôt supérieur à la dette fiscale.")); }

        // Actions
	};
}



