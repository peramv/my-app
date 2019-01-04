#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_suppress_code_invalid_for_non_clearing_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_suppress_code_invalid_for_non_clearing_account() { }
		~CIFast_IFast_ifastcbo_err_redemption_suppress_code_invalid_for_non_clearing_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_SUPPRESS_CODE_INVALID_FOR_NON_CLEARING_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Suppress Code Clearing cannot be selected for non Clearing Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suppress Code Clearing cannot be selected for non Clearing Account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Suppress Code Clearing cannot be selected for non Clearing Account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La compensation de code de suppression ne peut être sélectionnée pour un compte qui n'est pas un compte de compensation.")); }

        // Actions
	};
}



