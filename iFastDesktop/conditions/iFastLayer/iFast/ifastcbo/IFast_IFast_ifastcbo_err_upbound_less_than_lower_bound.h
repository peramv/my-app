#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_upbound_less_than_lower_bound : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_upbound_less_than_lower_bound() { }
		~CIFast_IFast_ifastcbo_err_upbound_less_than_lower_bound() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UPBOUND_LESS_THAN_LOWER_BOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Upper Bound value has to be greater than Lower Bound value.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Obergrenzen-Wert muss größer sein als Untergrenzen-Wert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El valor del límite superior debe ser mayor que el valor del límite inferior.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de limite maximale doit être supérieure à la valeur de limite minimale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De waarde van de bovengrens moet groter zijn dan de waarde van de ondergrens")); }

        // Actions
	};
}



