#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_has_stop_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_has_stop_redemption() { }
		~CIFast_IFast_ifastcbo_warn_account_has_stop_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_HAS_STOP_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption settlement is not allowed on this account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Redemption settlement is not allowed on this account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Règlement de rachat non autorisé pour ce compte")); }

        // Actions
	};
}



