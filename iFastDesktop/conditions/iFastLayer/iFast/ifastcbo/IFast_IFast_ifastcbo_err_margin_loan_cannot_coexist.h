#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_margin_loan_cannot_coexist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_margin_loan_cannot_coexist() { }
		~CIFast_IFast_ifastcbo_err_margin_loan_cannot_coexist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MARGIN_LOAN_CANNOT_COEXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Margin and Loan categories cannot coexist for the same account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Margin and Loan categories cannot coexist for the same account.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Margin and Loan categories cannot coexist for the same account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les catégories de marge et de prêt ne peuvent coexister pour le même compte.")); }

        // Actions
	};
}



