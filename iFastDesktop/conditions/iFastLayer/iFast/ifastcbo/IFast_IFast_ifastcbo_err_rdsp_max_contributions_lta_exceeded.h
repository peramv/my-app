#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_max_contributions_lta_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_max_contributions_lta_exceeded() { }
		~CIFast_IFast_ifastcbo_err_rdsp_max_contributions_lta_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_MAX_CONTRIBUTIONS_LTA_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("RDSP Maximum Contributions LTA exceeded.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("RDSP Maximum Contributions LTA exceeded.")); }

        // Actions
	};
}



