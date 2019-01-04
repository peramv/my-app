#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rdsp_amount_not_between_min_max : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rdsp_amount_not_between_min_max() { }
		~CIFast_IFast_ifastcbo_err_rdsp_amount_not_between_min_max() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RDSP_AMOUNT_NOT_BETWEEN_MIN_MAX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount not in Min/Max Range.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Amount not in Min/Max Range.")); }

        // Actions
	};
}



