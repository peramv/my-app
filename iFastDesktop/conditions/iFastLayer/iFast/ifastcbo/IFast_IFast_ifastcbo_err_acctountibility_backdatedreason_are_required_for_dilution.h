#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctountibility_backdatedreason_are_required_for_dilution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctountibility_backdatedreason_are_required_for_dilution() { }
		~CIFast_IFast_ifastcbo_err_acctountibility_backdatedreason_are_required_for_dilution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTOUNTIBILITY_BACKDATEDREASON_ARE_REQUIRED_FOR_DILUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountability code is mandatory for backdate trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Accountability code is mandatory for backdate trade.")); }

        // Actions
	};
}



