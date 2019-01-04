#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_non_resident_tax_jurid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_non_resident_tax_jurid() { }
		~CIFast_IFast_ifastcbo_warn_non_resident_tax_jurid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NON_RESIDENT_TAX_JURID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Type not available for non-resident")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type d'imposition invalide pour les non-résidents")); }

        // Actions
	};
}



