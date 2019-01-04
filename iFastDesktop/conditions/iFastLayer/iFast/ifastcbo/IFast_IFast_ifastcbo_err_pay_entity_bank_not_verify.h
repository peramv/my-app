#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pay_entity_bank_not_verify : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pay_entity_bank_not_verify() { }
		~CIFast_IFast_ifastcbo_err_pay_entity_bank_not_verify() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAY_ENTITY_BANK_NOT_VERIFY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to %OPERATION% due to pay entity bank is not verified.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de %OPERATION% parce que la banque de l'entité de paiement n'est pas vérifiée.")); }

        // Actions
	};
}



