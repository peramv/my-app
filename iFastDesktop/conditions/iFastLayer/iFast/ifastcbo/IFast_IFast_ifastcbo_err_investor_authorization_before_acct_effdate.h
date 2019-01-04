#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_investor_authorization_before_acct_effdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_investor_authorization_before_acct_effdate() { }
		~CIFast_IFast_ifastcbo_err_investor_authorization_before_acct_effdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVESTOR_AUTHORIZATION_BEFORE_ACCT_EFFDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date of Investor Authorization must be after Account Effective Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur de l'autorisation de l'investisseur doit être postérieure à la date d'entrée en vigueur du compte.")); }

        // Actions
	};
}



