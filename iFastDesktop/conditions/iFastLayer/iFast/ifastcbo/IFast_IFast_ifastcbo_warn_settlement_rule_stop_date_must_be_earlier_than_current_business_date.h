#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settlement_rule_stop_date_must_be_earlier_than_current_business_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settlement_rule_stop_date_must_be_earlier_than_current_business_date() { }
		~CIFast_IFast_ifastcbo_warn_settlement_rule_stop_date_must_be_earlier_than_current_business_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLEMENT_RULE_STOP_DATE_MUST_BE_EARLIER_THAN_CURRENT_BUSINESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop date must be earlier than current business date %CURRENT_BUS_DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt doit être antérieure à la date opérationnelle actuelle %CURRENT_BUS_DATE%.")); }		

        // Actions
	};
}