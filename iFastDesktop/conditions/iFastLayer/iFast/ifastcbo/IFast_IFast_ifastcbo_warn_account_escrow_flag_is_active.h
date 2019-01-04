#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_escrow_flag_is_active : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_escrow_flag_is_active() { }
		~CIFast_IFast_ifastcbo_warn_account_escrow_flag_is_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_ESCROW_FLAG_IS_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account escrow flag is active.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de mise en garantie du compte est actif.")); }

        // Actions
	};
}



