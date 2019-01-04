#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_balance_less_then_trans_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_balance_less_then_trans_amount() { }
		~CIFast_IFast_ifastcbo_err_balance_less_then_trans_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BALANCE_LESS_THEN_TRANS_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Balance is less than transaction amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du compte est inférieur au montant de la transaction.")); }

        // Actions
	};
}



