#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_assisted_contribution_amount_more_than_unassisted_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_assisted_contribution_amount_more_than_unassisted_amount() { }
		~CIFast_IFast_ifastcbo_warn_assisted_contribution_amount_more_than_unassisted_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ASSISTED_CONTRIBUTION_AMOUNT_MORE_THAN_UNASSISTED_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assisted Contribution amount is more than the Unassisted amount available for the tax year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de cotisation subventionnée est supérieur au montant non subventionné disponible pour l'année d'imposition.")); }

        // Actions
	};
}



