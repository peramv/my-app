#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_for_transaction_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_for_transaction_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_acct_for_transaction_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_FOR_TRANSACTION_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account for the transaction not available.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte pour la transaction n'est pas disponible.")); }

        // Actions
	};
}



