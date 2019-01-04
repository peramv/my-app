#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_account_should_match_systematic_currecncy : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_account_should_match_systematic_currecncy() { }
		~CIFast_IFast_ifastcbo_err_bank_account_should_match_systematic_currecncy() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_ACCOUNT_SHOULD_MATCH_SYSTEMATIC_CURRECNCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("In a non multi-currency environment, the currency of the systematic transaction %transdescription% (%fundcurrency%) does not match the currency (%bankcurrency%) of the bank account")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("In a non multi-currency environment, the currency of the systematic transaction %transdescription% (%fundcurrency%) does not match the currency (%bankcurrency%) of the bank account")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("In a non multi-currency environment, the currency of the systematic transaction %transdescription% (%fundcurrency%) does not match the currency (%bankcurrency%) of the bank account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Dans un environnement qui n'est pas multidevises, la monnaie de la transaction systématique %transdescription% (%fundcurrency%) ne correspond pas à la monnaie (%bankcurrency%) du compte bancaire.")); }

        // Actions
	};
}



