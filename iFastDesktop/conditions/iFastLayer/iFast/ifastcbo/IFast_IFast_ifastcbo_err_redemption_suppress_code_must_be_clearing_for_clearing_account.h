#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_suppress_code_must_be_clearing_for_clearing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_suppress_code_must_be_clearing_for_clearing_account() { }
		~CIFast_IFast_ifastcbo_err_redemption_suppress_code_must_be_clearing_for_clearing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_SUPPRESS_CODE_MUST_BE_CLEARING_FOR_CLEARING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Suppress Code must be Clearing for Clearing Account")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suppress Code must be Clearing for Clearing Account")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Suppress Code must be Clearing for Clearing Account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de suppression doit être Compensation pour un compte de compensation.")); }

        // Actions
	};
}



