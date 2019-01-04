#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_account_is_being_activated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_account_is_being_activated() { }
		~CIFast_IFast_ifastcbo_warn_account_is_being_activated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCOUNT_IS_BEING_ACTIVATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is being activated")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte est en cours d'activation.")); }

        // Actions
	};
}



