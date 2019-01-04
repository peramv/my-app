#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_loan_num_for_acctholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_loan_num_for_acctholder() { }
		~CIFast_IFast_ifastcbo_err_loan_num_for_acctholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LOAN_NUM_FOR_ACCTHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan Number only applicable for Accountholder Entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un numéro de prêt ne s'applique qu'au titulaire du compte.")); }

        // Actions
	};
}



