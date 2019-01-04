#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_commgroup_fund_class_can_not_coexist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_commgroup_fund_class_can_not_coexist() { }
		~CIFast_IFast_ifastcbo_err_commgroup_fund_class_can_not_coexist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COMMGROUP_FUND_CLASS_CAN_NOT_COEXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Commission group and Fund Code, Class Code cannot coexist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Commission group and Fund Code, Class Code cannot coexist.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Commission group and Fund Code, Class Code cannot coexist.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le groupe de commission, le code de fonds et le code de classe ne peuvent pas coexister.")); }

        // Actions
	};
}



