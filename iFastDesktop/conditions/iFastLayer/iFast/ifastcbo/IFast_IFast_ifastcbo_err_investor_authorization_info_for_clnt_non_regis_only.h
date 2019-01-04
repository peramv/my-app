#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_investor_authorization_info_for_clnt_non_regis_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_investor_authorization_info_for_clnt_non_regis_only() { }
		~CIFast_IFast_ifastcbo_err_investor_authorization_info_for_clnt_non_regis_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVESTOR_AUTHORIZATION_INFO_FOR_CLNT_NON_REGIS_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Investor Authorization setup is available only to non-register client held account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage de l'autorisation de l'investisseur n'est disponible que pour les comptes non enregistrés détenus par des clients.")); }

        // Actions
	};
}



