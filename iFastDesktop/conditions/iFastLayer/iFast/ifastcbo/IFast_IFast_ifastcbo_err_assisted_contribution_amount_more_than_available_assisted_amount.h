#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_assisted_contribution_amount_more_than_available_assisted_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_assisted_contribution_amount_more_than_available_assisted_amount() { }
		~CIFast_IFast_ifastcbo_err_assisted_contribution_amount_more_than_available_assisted_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_AVAILABLE_ASSISTED_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assisted Contribution amount to be reversed is more than the Assisted amount available for the tax year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de cotisation subventionnée qui sera renversé est supérieur au montant subventionné disponible pour l'année d'imposition.")); }

        // Actions
	};
}



