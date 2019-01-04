#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_suppress_paytype_required_for_fund_source : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_suppress_paytype_required_for_fund_source() { }
		~CIFast_IFast_ifastcbo_err_suppress_paytype_required_for_fund_source() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SUPPRESS_PAYTYPE_REQUIRED_FOR_FUND_SOURCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The pay type for this source of fund should be suppress.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de paiement pour cette source de fonds devrait être supprimé.")); }

        // Actions
	};
}



