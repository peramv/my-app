#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_salesrep_min_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_salesrep_min_balance() { }
		~CIFast_IFast_ifastcbo_err_salesrep_min_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALESREP_MIN_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales Rep: Less then minimum Fund/Class balance.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Représentant des ventes : inférieur au solde minimal du fonds/de la classe")); }

        // Actions
	};
}



