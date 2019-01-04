#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cesg_amount_be_returned_because_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cesg_amount_be_returned_because_redemption() { }
		~CIFast_IFast_ifastcbo_warn_cesg_amount_be_returned_because_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CESG_AMOUNT_BE_RETURNED_BECAUSE_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%PARAM_1% amount to be returned because of this redemption is $%PARAM_2%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%PARAM_1% montant à rembourser en raison du rachat $%PARAM_2%.")); }

        // Actions
	};
}



