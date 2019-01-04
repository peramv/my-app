#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_instructions_not_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_instructions_not_effective() { }
		~CIFast_IFast_ifastcbo_err_bank_instructions_not_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_INSTRUCTIONS_NOT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank instructions are effective as of %effectivedate%, and cannot be copied.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions bancaires sont en vigueur à partir du %effectivedate% et ne peuvent être copiées.")); }

        // Actions
	};
}



