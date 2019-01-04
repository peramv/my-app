#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_type_flat_for_bearer_certificate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_type_flat_for_bearer_certificate() { }
		~CIFast_IFast_ifastcbo_err_fee_type_flat_for_bearer_certificate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_TYPE_FLAT_FOR_BEARER_CERTIFICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee type should be flat for bearer certificate redemption code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee type should be flat for bearer certificate redemption code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de frais devrait être Fixes pour le code de rachat de certificat au porteur.")); }

        // Actions
	};
}



