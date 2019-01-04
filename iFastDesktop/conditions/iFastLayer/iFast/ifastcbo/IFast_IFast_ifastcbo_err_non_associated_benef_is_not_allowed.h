#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_associated_benef_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_associated_benef_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_non_associated_benef_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_ASSOCIATED_BENEF_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Historical RESP transferred-in notional balances for the QESI can only be entered for a beneficiary who is associated with the transfer-in transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'historique des soldes théoriques de transferts entrants REEE pour l'IQEE ne peut être saisie que pour un bénéficiaire associé à la transaction de transfert entrant.")); }

        // Actions
	};
}



