#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pre_percent_in_between : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pre_percent_in_between() { }
		~CIFast_IFast_ifastcbo_err_pre_percent_in_between() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRE_PERCENT_IN_BETWEEN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The percentage must be between %MIN% and %MAX%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The percentage must be between %MIN% and %MAX%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The percentage must be between %MIN% and %MAX%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage doit être situé entre %MIN% et %MAX%.")); }

        // Actions
	};
}



