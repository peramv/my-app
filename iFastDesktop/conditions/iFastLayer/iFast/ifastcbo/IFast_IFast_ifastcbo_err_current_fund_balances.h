#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_current_fund_balances : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_current_fund_balances() { }
		~CIFast_IFast_ifastcbo_err_current_fund_balances() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CURRENT_FUND_BALANCES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are current fund balances for this account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There are current fund balances for this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für dieses Konto liegen aktuelle Fonds-Saldos vor.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta cuenta tiene saldos en el fondo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des soldes de fonds courants pour ce compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn huidige fondssaldi voor dit account")); }

        // Actions
	};
}



