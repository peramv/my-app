#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_loan_type_for_escrow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_loan_type_for_escrow() { }
		~CIFast_IFast_ifastcbo_warn_loan_type_for_escrow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_LOAN_TYPE_FOR_ESCROW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Loan Type only applicable for Escrow Entity.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de prêt ne s'applique qu'au cessionnaire..")); }

        // Actions
	};
}



