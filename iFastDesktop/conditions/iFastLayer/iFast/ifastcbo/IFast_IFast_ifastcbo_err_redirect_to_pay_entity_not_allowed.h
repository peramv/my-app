#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redirect_to_pay_entity_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redirect_to_pay_entity_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_redirect_to_pay_entity_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDIRECT_TO_PAY_ENTITY_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redirect to Pay Entity is not allowed for EFT Purchase Trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réacheminement pour payer l'entité n'est pas autorisé pour une transaction d'achat TEF.")); }

        // Actions
	};
}



