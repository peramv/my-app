#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_sages_amount_to_be_returned_because_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_sages_amount_to_be_returned_because_redemption() { }
		~CIFast_IFast_ifastcbo_warn_sages_amount_to_be_returned_because_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SAGES_AMOUNT_TO_BE_RETURNED_BECAUSE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SAGES Amount to be returned because of the redemption: $%PARAM_1%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Montant de la SEEAS à rembourser en raison du rachat: $%PARAM_1%")); }

        // Actions
	};
}



