#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_beneficiary_not_eligible_for_qesi_increase_not_siblingonly : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_beneficiary_not_eligible_for_qesi_increase_not_siblingonly() { }
		~CIFast_IFast_ifastcbo_warn_beneficiary_not_eligible_for_qesi_increase_not_siblingonly() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BENEFICIARY_NOT_ELIGIBLE_FOR_QESI_INCREASE_NOT_SIBLINGONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary is not eligible for QESI Increase since Account is not siblingonly.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire n'est pas admissible pour une augmentation d'IQEE puisque le compte n'est pas Frère/sœur seulement.")); }

        // Actions
	};
}



