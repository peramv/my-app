#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_clnt_non_regis_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_clnt_non_regis_only() { }
		~CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_clnt_non_regis_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRCT_DEPT_PAYTYPE_FOR_CLNT_NON_REGIS_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Banking setup is available only to default banking of non-register client held account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage bancaire du TEF par dépôt direct n'est disponible que pour l'information bancaire par défaut des comptes non enregistrés détenus par des clients.")); }

        // Actions
	};
}



