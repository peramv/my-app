#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_trx_tiered_and_non_tiered_account_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_trx_tiered_and_non_tiered_account_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_trx_tiered_and_non_tiered_account_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TRX_TIERED_AND_NON_TIERED_ACCOUNT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer between Tiered and Non-Tiered Account is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un transfert entre des comptes progressif et non progressif n'est pas autorisé.")); }

        // Actions
	};
}



