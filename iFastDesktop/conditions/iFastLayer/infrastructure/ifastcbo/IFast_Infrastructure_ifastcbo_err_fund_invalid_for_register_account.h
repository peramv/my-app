#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fund_invalid_for_register_account : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fund_invalid_for_register_account() { }
		~CIFast_Infrastructure_ifastcbo_err_fund_invalid_for_register_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_INVALID_FOR_REGISTER_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Input Data Type cannot be blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ du type de données saisies ne peut être laissé vide.")); }

        // Actions
	};
}



