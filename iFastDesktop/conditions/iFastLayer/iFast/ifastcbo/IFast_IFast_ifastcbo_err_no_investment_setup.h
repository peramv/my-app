#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_investment_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_investment_setup() { }
		~CIFast_IFast_ifastcbo_err_no_investment_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_INVESTMENT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one investment item has to be set up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins un élément d’investissement doit être mis en place.")); }

        // Actions
	};
}



