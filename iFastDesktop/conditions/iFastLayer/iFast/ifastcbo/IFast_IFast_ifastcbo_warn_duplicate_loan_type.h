#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_duplicate_loan_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_duplicate_loan_type() { }
		~CIFast_IFast_ifastcbo_warn_duplicate_loan_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DUPLICATE_LOAN_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Loan Types are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Deux types de prêt identiques ne sont pas autorisés.")); }

        // Actions
	};
}



