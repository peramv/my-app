#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_loan_number_for_escrow_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_loan_number_for_escrow_account() { }
		~CIFast_IFast_ifastcbo_err_loan_number_for_escrow_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LOAN_NUMBER_FOR_ESCROW_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan Number only applicable for Accountholder of Escrow account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un numéro de prêt ne s'applique qu'au titulaire du compte cédé en garantie.")); }

        // Actions
	};
}



