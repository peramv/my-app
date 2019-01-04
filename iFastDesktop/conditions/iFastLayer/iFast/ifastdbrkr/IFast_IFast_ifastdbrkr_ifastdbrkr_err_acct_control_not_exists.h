#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_not_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_not_exists() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_acct_control_not_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_ACCT_CONTROL_NOT_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Control record does not exists")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du contrôle du compte n'existe pas.")); }

        // Actions
	};
}



