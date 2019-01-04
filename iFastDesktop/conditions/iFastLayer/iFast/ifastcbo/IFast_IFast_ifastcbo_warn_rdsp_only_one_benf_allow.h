#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_only_one_benf_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_only_one_benf_allow() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_only_one_benf_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_ONLY_ONE_BENF_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Beneficiary can not be more than one.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Beneficiary can not be more than one.")); }

        // Actions
	};
}



