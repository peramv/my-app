#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_broker_is_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_broker_is_not_effective() { }
		~CIFast_IFast_ifastcbo_err_fund_broker_is_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_BROKER_IS_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund broker is not effective.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund broker is not effective.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le courtier en fonds n'est pas en vigueur.")); }

        // Actions
	};
}



