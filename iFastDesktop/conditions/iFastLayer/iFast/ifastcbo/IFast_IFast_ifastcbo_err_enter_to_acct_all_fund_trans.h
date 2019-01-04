#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_enter_to_acct_all_fund_trans : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_enter_to_acct_all_fund_trans() { }
		~CIFast_IFast_ifastcbo_err_enter_to_acct_all_fund_trans() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTER_TO_ACCT_ALL_FUND_TRANS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Should enter to account for All Fund Transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie sollten das Zu-Konto für den Gesamtfonds-Transfer eingeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe introducirse en la cuenta para trasferencia de todo el fondo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez remplir le champ du compte cible pour le transfert de tous les fonds.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Naar-account moet worden ingevoerd voor overdracht van alle fondsen")); }

        // Actions
	};
}



