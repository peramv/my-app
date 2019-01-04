#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdsp_status_does_not_allow_contributions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdsp_status_does_not_allow_contributions() { }
		~CIFast_IFast_ifastcbo_warn_rdsp_status_does_not_allow_contributions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDSP_STATUS_DOES_NOT_ALLOW_CONTRIBUTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Registration Status doesn't allow contributions.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Registration Status doesn't allow contributions.")); }

        // Actions
	};
}



