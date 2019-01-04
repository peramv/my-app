#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_address_not_verify : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_address_not_verify() { }
		~CIFast_IFast_ifastcbo_warn_address_not_verify() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ADDRESS_NOT_VERIFY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payment address is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Adresse de paiement non vérifiée")); }

        // Actions
	};
}



