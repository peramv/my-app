#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_trade_not_allowed_for_tax_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_trade_not_allowed_for_tax_type() { }
		~CIFast_IFast_ifastcbo_err_cash_trade_not_allowed_for_tax_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_TRADE_NOT_ALLOWED_FOR_TAX_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash trade is not permitted for accounts with this tax type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une transaction comptant n'est pas autorisée pour les comptes de ce type d'imposition.")); }

        // Actions
	};
}



