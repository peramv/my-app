#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_swp_non_gmwb_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_swp_non_gmwb_funds() { }
		~CIFast_IFast_ifastcbo_warn_swp_non_gmwb_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SWP_NON_GMWB_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SWP cannot  include non-GMWB funds")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP ne peut pas inclure des fonds sans GRM.")); }

        // Actions
	};
}



