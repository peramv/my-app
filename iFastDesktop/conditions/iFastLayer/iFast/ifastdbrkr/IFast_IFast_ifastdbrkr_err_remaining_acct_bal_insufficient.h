#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_remaining_acct_bal_insufficient : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_remaining_acct_bal_insufficient() { }
		~CIFast_IFast_ifastdbrkr_err_remaining_acct_bal_insufficient() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REMAINING_ACCT_BAL_INSUFFICIENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Remaining account balance is insufficient to cover the remaining minimum.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verbleibender Kontosaldo reicht zur Deckung des verbleibenden Minimums nicht aus.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo de cuenta no es suficiente para cubrir el mínimo restante.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde restant au compte est insuffisant pour couvrir le minimum restant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Resterende accountsaldo is onvoldoende om het resterende minimum te dekken")); }

        // Actions
	};
}



