#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_lifetime_contrib_limit_set_up : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_lifetime_contrib_limit_set_up() { }
		~CIFast_IFast_ifastcbo_err_no_lifetime_contrib_limit_set_up() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_LIFETIME_CONTRIB_LIMIT_SET_UP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Lifetime Contribution Limits has been set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun plafond viager de cotisation n'a été réglé.")); }

        // Actions
	};
}



