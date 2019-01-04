#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_system_acct_category : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_system_acct_category() { }
		~CIFast_IFast_ifastcbo_err_system_acct_category() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SYSTEM_ACCT_CATEGORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This account category can be set by system only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette catégorie de compte ne peut être réglée que par le système.")); }

        // Actions
	};
}



