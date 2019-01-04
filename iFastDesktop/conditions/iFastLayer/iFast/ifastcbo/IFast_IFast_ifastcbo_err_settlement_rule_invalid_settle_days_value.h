#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_rule_invalid_settle_days_value : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_rule_invalid_settle_days_value() { }
		~CIFast_IFast_ifastcbo_err_settlement_rule_invalid_settle_days_value() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_RULE_INVALID_SETTLE_DAYS_VALUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement rule has invalid settle days value.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La règle de règlement comporte une valeur de jours de règlement invalide.")); }

        // Actions
	};
}



