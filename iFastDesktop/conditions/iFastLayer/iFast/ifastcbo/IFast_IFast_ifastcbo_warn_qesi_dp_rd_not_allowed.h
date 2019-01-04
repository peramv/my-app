#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_qesi_dp_rd_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_qesi_dp_rd_not_allowed() { }
		~CIFast_IFast_ifastcbo_warn_qesi_dp_rd_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_QESI_DP_RD_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("DP 78,79,80,81 or RD Q1,Q2,Q3 are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("DP 78, 79, 80, 81 ou RD Q1, Q2, Q3 ne sont pas autorisés.")); }

        // Actions
	};
}



