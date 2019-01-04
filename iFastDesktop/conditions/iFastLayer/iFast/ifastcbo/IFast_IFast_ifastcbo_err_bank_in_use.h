#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_bank_in_use : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_bank_in_use() { }
		~CIFast_IFast_ifastcbo_err_bank_in_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BANK_IN_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Bank Instruction is used by pending or unsettled trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information bancaire est utilisée par une transaction en suspens ou non réglée.")); }

        // Actions
	};
}



