#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_loan_type_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_loan_type_mandatory() { }
		~CIFast_IFast_ifastcbo_warn_loan_type_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LOAN_TYPE_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan Type is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de prêt doit être indiqué.")); }

        // Actions
	};
}



