#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_only_pay_to_entity_paytype_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_only_pay_to_entity_paytype_allowed() { }
		~CIFast_IFast_ifastcbo_err_only_pay_to_entity_paytype_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ONLY_PAY_TO_ENTITY_PAYTYPE_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only redirect to pay to entity pay type is allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le type de paiement Paiement à l'entité est autorisé.")); }

        // Actions
	};
}



