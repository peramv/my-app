#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_shrhldr_addr_not_verified_for_settlement : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_shrhldr_addr_not_verified_for_settlement() { }
		~CIFast_IFast_ifastdbrkr_err_shrhldr_addr_not_verified_for_settlement() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SHRHLDR_ADDR_NOT_VERIFIED_FOR_SETTLEMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to settle trade due to payment address is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de régler la transaction car l'adresse de paiement n'est pas vérifiée.")); }

        // Actions
	};
}



