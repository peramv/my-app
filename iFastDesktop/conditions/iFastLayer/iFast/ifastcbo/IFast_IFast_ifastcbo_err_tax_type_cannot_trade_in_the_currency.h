#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_type_cannot_trade_in_the_currency : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_type_cannot_trade_in_the_currency() { }
		~CIFast_IFast_ifastcbo_err_tax_type_cannot_trade_in_the_currency() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_TYPE_CANNOT_TRADE_IN_THE_CURRENCY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax type cannot trade in the currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Steuerart darf nicht in der Währung verwendet werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo tributario no puede operar en esta divisa")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les opérations de ce type d'imposition sont impossibles dans la monnaie.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Belastingtype kan handelen in de valuta")); }

        // Actions
	};
}



