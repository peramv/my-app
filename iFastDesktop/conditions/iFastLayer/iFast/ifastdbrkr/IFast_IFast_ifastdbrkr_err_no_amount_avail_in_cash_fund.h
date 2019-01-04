#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_amount_avail_in_cash_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_amount_avail_in_cash_fund() { }
		~CIFast_IFast_ifastdbrkr_err_no_amount_avail_in_cash_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_AMOUNT_AVAIL_IN_CASH_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Amount Available in Cash-holding Fund.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Betrag in Bargeldbestand-Fonds verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Amount Available in Cash-holding Fund.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun montant disponible dans le fonds de liquidité")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("No Amount Available in Cash-holding Fund")); }

        // Actions
	};
}



