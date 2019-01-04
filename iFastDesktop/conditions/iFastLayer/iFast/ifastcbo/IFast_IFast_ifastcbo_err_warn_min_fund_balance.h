#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_min_fund_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_min_fund_balance() { }
		~CIFast_IFast_ifastcbo_err_warn_min_fund_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MIN_FUND_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% Class %CLASS% balance will be less than minimum:  %MINIMUM_BAL%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fonds %FUND% / Klasse %CLASS% -Saldo wird unter dem Minimum liegen:  %MINIMUM_BAL%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo del fondo %FUND% / clase %CLASS% será inferior al mínimo:  %MINIMUM_BAL%. .")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du fonds %FUND% et de la classe %CLASS% sera inférieur au minimum : %MINIMUM_BAL%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Saldo fonds %FUND%/categorie %CLASS% zal minder zijn dan het minimum:  %MINIMUM_BAL%")); }

        // Actions
	};
}



