#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_code_coexist_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_code_coexist_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_fee_code_coexist_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_CODE_COEXIST_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee code 18 and 180 cannot be co-exists and effective under the same period at account level fee set up.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee code 18 and 180 cannot be co-exists and effective under the same period at account level fee set up.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fee code 18 and 180 cannot be co-exists and effective under the same period at account level fee set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les codes de frais 18 et 180 ne peuvent coexister et être en vigueur pendant la même période au réglage des frais au niveau du compte.")); }

        // Actions
	};
}



