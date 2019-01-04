#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_lifetime_contrib_limits_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_lifetime_contrib_limits_not_setup() { }
		~CIFast_IFast_ifastcbo_err_lifetime_contrib_limits_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LIFETIME_CONTRIB_LIMITS_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Lifetime Contribution Limits has been set up for %BENNAME%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun plafond viager de cotisation n'a été réglé pour %BENNAME%.")); }

        // Actions
	};
}



