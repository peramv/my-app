#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_unable_to_modify : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_unable_to_modify() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_unable_to_modify() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ACCT_CONTROL_UNABLE_TO_MODIFY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to modify AcctControls, version numbers are different")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de modifier les contrôles du compte, les numéros de version sont différents.")); }

        // Actions
	};
}



