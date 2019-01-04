#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_net_amount_less_then_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_net_amount_less_then_zero() { }
		~CIFast_IFast_ifastcbo_err_net_amount_less_then_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NET_AMOUNT_LESS_THEN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net Amount can not be less than 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nettobetrag darf nicht unter 0,0 liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto neto no puede ser menor que 0.0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant net ne peut être inférieur à zéro.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Netto bedrag kan niet minder dan 0,0 zijn")); }

        // Actions
	};
}



