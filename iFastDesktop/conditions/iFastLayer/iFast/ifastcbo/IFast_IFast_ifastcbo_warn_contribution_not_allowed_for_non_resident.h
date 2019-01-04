#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_contribution_not_allowed_for_non_resident : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_contribution_not_allowed_for_non_resident() { }
		~CIFast_IFast_ifastcbo_warn_contribution_not_allowed_for_non_resident() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CONTRIBUTION_NOT_ALLOWED_FOR_NON_RESIDENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contribution not allowed for non-resident for the Tax Type")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cotisation non autorisée pour les non-résidents pour le type d'imposition")); }

        // Actions
	};
}



