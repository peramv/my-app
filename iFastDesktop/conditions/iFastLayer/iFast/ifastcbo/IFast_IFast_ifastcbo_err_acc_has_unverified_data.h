#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_has_unverified_data : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_has_unverified_data() { }
		~CIFast_IFast_ifastcbo_err_account_has_unverified_data() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_HAS_UNVERIFIED_DATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account has unverified data.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte a des données non vérifiées.")); }

        // Actions
	};
}



