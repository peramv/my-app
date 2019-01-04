#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_loan_num : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_loan_num() { }
		~CIFast_IFast_ifastcbo_err_duplicate_loan_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_LOAN_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Loan Numbers are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Des numéros de prêt identiques ne sont pas autorisés.")); }

        // Actions
	};
}



