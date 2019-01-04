#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_qesi_life_time_grant_limit_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_qesi_life_time_grant_limit_exceeded() { }
		~CIFast_IFast_ifastcbo_err_qesi_life_time_grant_limit_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_QESI_LIFE_TIME_GRANT_LIMIT_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Life Time Grant Limit Exceeded.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plafond viager de subvention IQEE excédé")); }

        // Actions
	};
}



