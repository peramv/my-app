#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_bonimax_value_less_than_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_bonimax_value_less_than_zero() { }
		~CIFast_IFast_ifastdbrkr_err_bonimax_value_less_than_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BONIMAX_VALUE_LESS_THAN_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bonimax value is less than 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bonimax value is less than 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur maximale de boni est inférieure à zéro.")); }

        // Actions
	};
}



