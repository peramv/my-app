#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_net_annual_contribution_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_net_annual_contribution_is_zero() { }
		~CIFast_IFast_ifastcbo_warn_net_annual_contribution_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NET_ANNUAL_CONTRIBUTION_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Net annual Contribution for the year %PARAM_1% is zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La cotisation annuelle nette pour l'année %PARAM_1% est de zéro.")); }

        // Actions
	};
}



