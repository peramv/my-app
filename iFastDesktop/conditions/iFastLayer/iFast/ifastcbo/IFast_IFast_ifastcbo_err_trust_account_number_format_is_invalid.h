#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trust_account_number_format_is_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trust_account_number_format_is_invalid() { }
		~CIFast_IFast_ifastcbo_err_trust_account_number_format_is_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRUST_ACCOUNT_NUMBER_FORMAT_IS_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trust Account Number format is invalid")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le format du numéro de compte de fiducie est invalide.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please check ID value.")); }
	};
}



