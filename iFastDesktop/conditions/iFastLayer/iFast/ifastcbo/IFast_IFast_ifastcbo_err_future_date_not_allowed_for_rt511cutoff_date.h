#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_date_not_allowed_for_rt511cutoff_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_date_not_allowed_for_rt511cutoff_date() { }
		~CIFast_IFast_ifastcbo_err_future_date_not_allowed_for_rt511cutoff_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DATE_NOT_ALLOWED_FOR_RT511CUTOFF_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cut-Off Date cannot be future date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date limite ne peut être postérieure à la date actuelle.")); }

        // Actions
	};
}



