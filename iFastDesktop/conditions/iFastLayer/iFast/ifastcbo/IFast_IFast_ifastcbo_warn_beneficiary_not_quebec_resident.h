#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_beneficiary_not_quebec_resident : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_beneficiary_not_quebec_resident() { }
		~CIFast_IFast_ifastcbo_warn_beneficiary_not_quebec_resident() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BENEFICIARY_NOT_QUEBEC_RESIDENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Beneficiary is not a resident of Quebec.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le bénéficiaire n'est pas un résident du Québec.")); }

        // Actions
	};
}



