#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_enter_valid_account_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_enter_valid_account_number() { }
		~CIFast_IFast_ifastcbo_err_enter_valid_account_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENTER_VALID_ACCOUNT_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please enter a valid account number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Please enter a valid account number.")); }

        // Actions
	};
}



