#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_insufficient_notional_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_insufficient_notional_balance() { }
		~CIFast_IFast_ifastdbrkr_err_insufficient_notional_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUFFICIENT_NOTIONAL_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient notional balance to cancel RESP transfer")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde théorique est insuffisant pour annuler le transfert REEE.")); }

        // Actions
	};
}



