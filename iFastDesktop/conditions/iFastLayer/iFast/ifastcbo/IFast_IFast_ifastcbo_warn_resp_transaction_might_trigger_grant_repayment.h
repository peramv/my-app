#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_resp_transaction_might_trigger_grant_repayment : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_resp_transaction_might_trigger_grant_repayment() { }
		~CIFast_IFast_ifastcbo_warn_resp_transaction_might_trigger_grant_repayment() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RESP_TRANSACTION_MIGHT_TRIGGER_GRANT_REPAYMENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You have entered a transaction which might trigger grant repayment, please verify and return corresponding grant.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous avez saisi une transaction qui pourrai déclencher un remboursement de subvention, veuillez vérifier et rembourser la subvention correspondante.")); }

        // Actions
	};
}



