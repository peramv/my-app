#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_commitment_product_not_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_commitment_product_not_active() { }
		~CIFast_IFast_ifastcbo_err_commitment_product_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMITMENT_PRODUCT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commitment Product is not active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le produit d'engagement est inactif.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please select another product")); }
	};
}



