#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fee_code_not_defined_unable_store_deduction_fee : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fee_code_not_defined_unable_store_deduction_fee() { }
		~CIFast_IFast_ifastcbo_warn_fee_code_not_defined_unable_store_deduction_fee() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FEE_CODE_NOT_DEFINED_UNABLE_STORE_DEDUCTION_FEE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Code is not defined, cannot store deducted fee.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de frais indéfini, impossible de stocker les frais déduits.")); }

        // Actions
	};
}



