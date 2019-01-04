#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_ltd_contrib_must_equal_sum_of_pre98_cesgac_cesguc: public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_ltd_contrib_must_equal_sum_of_pre98_cesgac_cesguc() { }
		~CIFast_IFast_ifastcbo_warn_ltd_contrib_must_equal_sum_of_pre98_cesgac_cesguc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LTD_CONTRIB_MUST_EQUAL_SUM_OF_PRE98_CESGAC_CESGUC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("LTD Contribution must be equal to the total of Pre-1998 + CESG Assisted + CESG Unassisted amounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La contribution ILT doit être égale au total pré-1998 + montants subventionnés et non subventionnés de CEES.")); }

        // Actions
	};
}



