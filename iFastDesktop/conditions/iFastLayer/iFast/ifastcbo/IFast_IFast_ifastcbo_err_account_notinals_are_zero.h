#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_notinals_are_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_notinals_are_zero() { }
		~CIFast_IFast_ifastcbo_err_account_notinals_are_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NOTINALS_ARE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account level RESP notional information is not entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'information théorique REEE au niveau du compte n'a pas été saisie.")); }

        // Actions
	};
}



