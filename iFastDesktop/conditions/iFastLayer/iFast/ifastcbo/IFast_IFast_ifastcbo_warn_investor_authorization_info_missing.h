#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_investor_authorization_info_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_investor_authorization_info_missing() { }
		~CIFast_IFast_ifastcbo_warn_investor_authorization_info_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_INVESTOR_AUTHORIZATION_INFO_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to find matching Investor Authorization information for Direcrt Deposit Banking on  %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de trouver l'information correspondante sur l'autorisation de l'investisseur pour l'information bancaire du TEF par dépôt direct pour le %DATE%.")); }

        // Actions
	};
}



