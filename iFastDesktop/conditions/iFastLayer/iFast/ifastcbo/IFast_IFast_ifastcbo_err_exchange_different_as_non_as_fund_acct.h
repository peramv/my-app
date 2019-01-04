#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exchange_different_as_non_as_fund_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exchange_different_as_non_as_fund_acct() { }
		~CIFast_IFast_ifastcbo_err_exchange_different_as_non_as_fund_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCHANGE_DIFFERENT_AS_NON_AS_FUND_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exchange AS fund/Non-AS fund for different account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Devisen-AS/Nicht-AS-Fonds für verschiedene Konten")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cambie el fondo AS/no AS por otras cuentas")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échange de fonds AS et non AS pour différents comptes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ruil AS-fonds/niet-AS-fonds in voor ander account")); }

        // Actions
	};
}



