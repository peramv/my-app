#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_err_fund_in_foreign_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_err_fund_in_foreign_currency() { }
		~CIFast_IFast_ifastcbo_err_err_fund_in_foreign_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_FUND_IN_FOREIGN_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% Class %CLASS% in Transaction %TRANS_NUM% is in %FOREIGN_CURRENCY% currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Dieser Fonds ist in der Währung %FOREIGN_CURRENCY%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este fondo está denominado en %FOREIGN_CURRENCY%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fond %FUND% et la classe %CLASS% de la transaction %TRANS_NUM% sont en monnaie de %FOREIGN_CURRENCY%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit fonds is in %FOREIGN_CURRENCY% valuta")); }

        // Actions
	};
}



