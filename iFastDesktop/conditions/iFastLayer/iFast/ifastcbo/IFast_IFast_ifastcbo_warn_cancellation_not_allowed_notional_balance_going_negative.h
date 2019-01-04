#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_cancellation_not_allowed_notional_balance_going_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_cancellation_not_allowed_notional_balance_going_negative() { }
		~CIFast_IFast_ifastcbo_warn_cancellation_not_allowed_notional_balance_going_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CANCELLATION_NOT_ALLOWED_NOTIONAL_BALANCE_GOING_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Your action will create a negative Notional balance, please review subsequent transactions in this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Votre action créera un solde théorique négatif, veuillez vérifier les transactions suivantes dans ce compte.")); }

        // Actions
	};
}



