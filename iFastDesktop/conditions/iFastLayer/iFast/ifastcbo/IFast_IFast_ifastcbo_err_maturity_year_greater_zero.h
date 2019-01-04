#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_maturity_year_greater_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_maturity_year_greater_zero() { }
		~CIFast_IFast_ifastcbo_err_maturity_year_greater_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MATURITY_YEAR_GREATER_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity years have to be greater than 0.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Maturity years have to be greater than 0.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Maturity years have to be greater than 0.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les années d'échéance doivent être supérieures à zéro.")); }

        // Actions
	};
}



