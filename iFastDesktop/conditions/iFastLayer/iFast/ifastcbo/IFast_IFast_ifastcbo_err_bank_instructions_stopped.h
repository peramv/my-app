#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_instructions_stopped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_instructions_stopped() { }
		~CIFast_IFast_ifastcbo_err_bank_instructions_stopped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_INSTRUCTIONS_STOPPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank instructions are stopped as of %stopdate%, and cannot be copied.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les instructions bancaires sont arrêtées à partir du %stopdate% et ne peuvent être copiées.")); }

        // Actions
	};
}



