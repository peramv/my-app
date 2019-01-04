#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_default_bank_info_for_acct_distrib_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_default_bank_info_for_acct_distrib_not_found() { }
		~CIFast_IFast_ifastcbo_warn_default_bank_info_for_acct_distrib_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEFAULT_BANK_INFO_FOR_ACCT_DISTRIB_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no banking information for account level distribution instruction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information bancaire sur les instructions de distribution au niveau du compte")); }

        // Actions
	};
}



