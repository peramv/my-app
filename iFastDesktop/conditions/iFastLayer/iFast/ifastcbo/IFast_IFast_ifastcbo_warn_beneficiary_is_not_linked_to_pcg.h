#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_beneficiary_is_not_linked_to_pcg : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_beneficiary_is_not_linked_to_pcg() { }
		~CIFast_IFast_ifastcbo_warn_beneficiary_is_not_linked_to_pcg() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BENEFICIARY_IS_NOT_LINKED_TO_PCG")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary is not linked to a PCG.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire n'est lié à aucun responsable principal.")); }

        // Actions
	};
}



