#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acq_fee_option_only_applicable_for_3rd_party_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acq_fee_option_only_applicable_for_3rd_party_funds() { }
		~CIFast_IFast_ifastcbo_err_acq_fee_option_only_applicable_for_3rd_party_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACQ_FEE_OPTION_ONLY_APPLICABLE_FOR_3RD_PARTY_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%acqoption% is only applicable for 3rd party funds.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%acqoption% is only applicable for 3rd party funds.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'option %acqoption% n'est applicable qu'aux fonds de tiers.")); }

        // Actions
	};
}



