#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_assisted_amt_is_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_assisted_amt_is_zero() { }
		~CIFast_IFast_ifastcbo_warn_assisted_amt_is_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ASSISTED_AMT_IS_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Assisted Contribution amount is zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de cotisation subventionnée est de zéro.")); }

        // Actions
	};
}



