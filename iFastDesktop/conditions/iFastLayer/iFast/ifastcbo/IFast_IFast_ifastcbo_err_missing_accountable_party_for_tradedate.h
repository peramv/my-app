#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_missing_accountable_party_for_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_missing_accountable_party_for_tradedate() { }
		~CIFast_IFast_ifastcbo_err_missing_accountable_party_for_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MISSING_ACCOUNTABLE_PARTY_FOR_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Missing accountable party from trade date on.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Partie comptable manquante en date de la transaction")); }

        // Actions
	};
}



