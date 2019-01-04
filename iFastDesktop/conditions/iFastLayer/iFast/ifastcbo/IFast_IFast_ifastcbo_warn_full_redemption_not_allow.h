#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_full_redemption_not_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_full_redemption_not_allow() { }
		~CIFast_IFast_ifastcbo_warn_full_redemption_not_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FULL_REDEMPTION_NOT_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The requested full redemption should not be allowed because Legislative rules are violated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The requested full redemption should not be allowed because Legislative rules are violated.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The requested full redemption should not be allowed because Legislative rules are violated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande de rachat total ne devrait pas être autorisée parce que des règles législatives sont violées.")); }

        // Actions
	};
}



