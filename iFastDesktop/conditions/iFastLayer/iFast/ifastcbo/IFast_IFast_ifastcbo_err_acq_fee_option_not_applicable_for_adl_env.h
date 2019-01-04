#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acq_fee_option_not_applicable_for_adl_env : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acq_fee_option_not_applicable_for_adl_env() { }
		~CIFast_IFast_ifastcbo_err_acq_fee_option_not_applicable_for_adl_env() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACQ_FEE_OPTION_NOT_APPLICABLE_FOR_ADL_ENV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%acqoption% is not applicable in an antidilution environment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%acqoption% is not applicable in an antidilution environment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%acqoption% n'est pas applicable dans un environnement antidilution.")); }

        // Actions
	};
}



