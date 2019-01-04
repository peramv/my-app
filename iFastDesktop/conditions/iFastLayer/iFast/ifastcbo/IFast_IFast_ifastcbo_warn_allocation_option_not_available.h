#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_allocation_option_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_allocation_option_not_available() { }
		~CIFast_IFast_ifastcbo_warn_allocation_option_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ALLOCATION_OPTION_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation option not available (in this environment).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Option non disponible (dans cet environnement) de répartition.")); }

        // Actions
	};
}



