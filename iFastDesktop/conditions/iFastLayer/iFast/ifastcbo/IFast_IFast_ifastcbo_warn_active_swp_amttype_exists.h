#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_active_swp_amttype_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_active_swp_amttype_exists() { }
		~CIFast_IFast_ifastcbo_warn_active_swp_amttype_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACTIVE_SWP_AMTTYPE_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("An Active SWP already exists with Amount Type GWA or LWA.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un PRP actif existe déjà avec un MRV ou un MRG.")); }

        // Actions
	};
}



