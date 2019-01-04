#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_to_account_cannot_be_same_as_from_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_to_account_cannot_be_same_as_from_account() { }
		~CIFast_IFast_ifastcbo_err_to_account_cannot_be_same_as_from_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TO_ACCOUNT_CANNOT_BE_SAME_AS_FROM_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To account number can not be the same as current account number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("To account number can not be the same as current account number.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("To account number can not be the same as current account number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte cible ne peut être identique au numéro de compte actuel.")); }

        // Actions
	};
}



