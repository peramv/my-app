#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_client_condition_rate_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_client_condition_rate_is_zero() { }
		~CIFast_IFast_ifastcbo_warn_client_condition_rate_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CLIENT_CONDITION_RATE_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Client condition rate is zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Client condition rate is zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux de condition du client est de zéro.")); }

        // Actions
	};
}



