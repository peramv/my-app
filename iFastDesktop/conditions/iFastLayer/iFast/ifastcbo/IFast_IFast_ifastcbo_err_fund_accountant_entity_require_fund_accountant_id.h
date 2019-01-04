#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_accountant_entity_require_fund_accountant_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_accountant_entity_require_fund_accountant_id() { }
		~CIFast_IFast_ifastcbo_err_fund_accountant_entity_require_fund_accountant_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_ACCOUNTANT_ENTITY_REQUIRE_FUND_ACCOUNTANT_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Accountant Entity requires Fund Accountant ID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité comptable du fonds requiert un code de comptable de fonds.")); }

        // Actions
	};
}



