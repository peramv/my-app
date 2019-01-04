#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_exchange_different_as_fund_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_exchange_different_as_fund_acct() { }
		~CIFast_IFast_ifastcbo_err_warn_exchange_different_as_fund_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_EXCHANGE_DIFFERENT_AS_FUND_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange AS fund for different accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Devisen-AS-Fonds für verschiedene Konten")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cambie el fondo AS por otras cuentas")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ruil AS-fonds in voor andere accounts")); }

        // Actions
	};
}



