#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_client_rrsp_rrif_loan_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_client_rrsp_rrif_loan_acct() { }
		~CIFast_IFast_ifastcbo_err_client_rrsp_rrif_loan_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CLIENT_RRSP_RRIF_LOAN_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan category is applicable only for client RRSP or RRIF accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Loan category is applicable only for client RRSP or RRIF accounts.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Loan category is applicable only for client RRSP or RRIF accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie du prêt est uniquement applicable pour les comptes clients REER ou FERR.")); }

        // Actions
	};
}



