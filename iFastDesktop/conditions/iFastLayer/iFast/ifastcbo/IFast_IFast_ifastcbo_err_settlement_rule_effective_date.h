#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_rule_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_rule_effective_date() { }
		~CIFast_IFast_ifastcbo_err_settlement_rule_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_RULE_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement Rule Effective Date is After Stop Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur de la règle de règlement est postérieure à la date d'arrêt.")); }

        // Actions
	};
}



