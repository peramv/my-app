#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_dirct_dept_bank_only : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_dirct_dept_bank_only() { }
		~CIFast_IFast_ifastcbo_err_dirct_dept_paytype_for_dirct_dept_bank_only() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DIRCT_DEPT_PAYTYPE_FOR_DIRCT_DEPT_BANK_ONLY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Direct Deposit EFT Paytype is for A\\C has Direct Deposit Bank setup only.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de paiement du TEF par dépôt direct n'est que pour les comptes qui comportent un réglage bancaire de dépôt direct.")); }

        // Actions
	};
}



