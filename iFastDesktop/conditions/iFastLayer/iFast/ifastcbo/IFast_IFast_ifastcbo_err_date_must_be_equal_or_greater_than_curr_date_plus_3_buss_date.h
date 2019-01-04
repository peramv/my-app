#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_must_be_equal_or_greater_than_curr_date_plus_3_buss_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_must_be_equal_or_greater_than_curr_date_plus_3_buss_date() { }
		~CIFast_IFast_ifastcbo_err_date_must_be_equal_or_greater_than_curr_date_plus_3_buss_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_MUST_BE_EQUAL_OR_GREATER_THAN_CURR_DATE_PLUS_3_BUSS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The date must be equal or greater than current Cycle date + 3 business dates.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date doit se situer après ou être équivalente à la date actuelle du cycle + 3 jours ouvrables.")); }

        // Actions
	};
}



