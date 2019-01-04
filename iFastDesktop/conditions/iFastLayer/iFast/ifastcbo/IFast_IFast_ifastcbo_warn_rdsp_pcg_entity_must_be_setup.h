#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_pcg_entity_must_be_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_pcg_entity_must_be_setup() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_pcg_entity_must_be_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_PCG_ENTITY_MUST_BE_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Primary Care Giver is mandatory as beneficiary is age 18 years or less.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Primary Care Giver is mandatory as beneficiary is age 18 years or less.")); }		

        // Actions
	};
}



