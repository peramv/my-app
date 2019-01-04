#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eft_full_redemption_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eft_full_redemption_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_eft_full_redemption_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFT_FULL_REDEMPTION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account holdings are not in the same currency. EFT full redemption not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Account holdings are not in the same currency. EFT full redemption not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le portefeuille du compte n'est pas dans la même monnaie. Rachat total TEF non autorisé.")); }

        // Actions
	};
}



