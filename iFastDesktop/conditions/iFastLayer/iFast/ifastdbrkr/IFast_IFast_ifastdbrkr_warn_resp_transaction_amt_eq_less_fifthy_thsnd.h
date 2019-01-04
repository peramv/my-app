#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_warn_resp_transaction_amt_eq_less_fifthy_thsnd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_warn_resp_transaction_amt_eq_less_fifthy_thsnd() { }
		~CIFast_IFast_ifastdbrkr_warn_resp_transaction_amt_eq_less_fifthy_thsnd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_TRANSACTION_AMT_EQ_LESS_FIFTHY_THSND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You have entered a transaction amount equal to or less than $50,000.00. As a result, a grant repayment of $0.00 MUST be reported to HRDC.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous avez entré un montant de transaction égal ou inférieur à 50 000,00 $. En conséquence, un remboursement de subvention de 0,00 $ DOIT être déclaré au DRHC.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Reminder: Run 'Generation of Zero Grant Repayment'.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Rappel : exécutez Génération du non-remboursement de subvention à zéro")); }
	};
}



