#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_notional_paid_by_other_amounts_must_be_positive : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_notional_paid_by_other_amounts_must_be_positive() { }
		~CIFast_IFast_ifastcbo_err_notional_paid_by_other_amounts_must_be_positive() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAID_BY_OTHER_NOTIONAL_AMOUNTS_MUST_BE_POSITIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Paid By Other Institution is a balance and must be positive.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Payé par une autre institution » est un solde et doit être positif.")); }
		
        // Actions
	};
}



