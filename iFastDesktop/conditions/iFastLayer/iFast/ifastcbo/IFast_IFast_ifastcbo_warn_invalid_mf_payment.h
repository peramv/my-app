#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_invalid_mf_payment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_invalid_mf_payment() { }
		~CIFast_IFast_ifastcbo_warn_invalid_mf_payment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVALID_MF_PAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid payment period.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Période de paiement invalide")); }

        // Actions
	};
}



