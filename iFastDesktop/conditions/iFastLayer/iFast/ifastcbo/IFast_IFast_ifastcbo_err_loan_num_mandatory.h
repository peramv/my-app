#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_loan_num_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_loan_num_mandatory() { }
		~CIFast_IFast_ifastcbo_err_loan_num_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LOAN_NUM_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan Number is missing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de prêt est manquant.")); }

        // Actions
	};
}



