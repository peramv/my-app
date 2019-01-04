#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_feecode_not_valid_for_non_pf_funds : public CConditionObject  
	{
	public:
		CIFast_IFast_ifastcbo_err_feecode_not_valid_for_non_pf_funds() { }
		~CIFast_IFast_ifastcbo_err_feecode_not_valid_for_non_pf_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEECODE_NOT_VALID_FOR_NON_PF_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee can be applied to PF Funds Only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fee peut être appliqué aux fonds PF Seuls.")); }

        // Actions
	};
}



