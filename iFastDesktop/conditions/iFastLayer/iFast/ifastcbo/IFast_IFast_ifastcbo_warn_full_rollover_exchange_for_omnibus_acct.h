#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_full_rollover_exchange_for_omnibus_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_full_rollover_exchange_for_omnibus_acct() { }
		~CIFast_IFast_ifastcbo_warn_full_rollover_exchange_for_omnibus_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FULL_ROLLOVER_EXCHANGE_FOR_OMNIBUS_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A full Rollover-Exchange is indicated for Omnibus Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert avec report total d’impôt est indiqué pour le compte Omnibus.")); }

        // Actions
	};
}



