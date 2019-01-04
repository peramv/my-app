#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_custodian_entity_require_fund_custodian_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_custodian_entity_require_fund_custodian_id() { }
		~CIFast_IFast_ifastcbo_err_fund_custodian_entity_require_fund_custodian_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CUSTODIAN_ENTITY_REQUIRE_FUND_CUSTODIAN_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Custodian Entity requires Fund Custodian ID.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité dépositaire du fonds requiert un code de dépositaire de fonds.")); }

        // Actions
	};
}



