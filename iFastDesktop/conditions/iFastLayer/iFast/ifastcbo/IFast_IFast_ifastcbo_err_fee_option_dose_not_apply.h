#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_option_dose_not_apply : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_option_dose_not_apply() { }
		~CIFast_IFast_ifastcbo_err_fee_option_dose_not_apply() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_OPTION_DOSE_NOT_APPLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%acqoption% is not applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option %acqoption% n'est pas applicable.")); }

        // Actions
	};
}



