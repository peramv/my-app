#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fromdate_before_acct_inception_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fromdate_before_acct_inception_date() { }
		~CIFast_IFast_ifastcbo_err_fromdate_before_acct_inception_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FROMDATE_BEFORE_ACCT_INCEPTION_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From Date is before account inception date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date source est antérieure à la date de prise d'effet du compte.")); }

        // Actions
	};
}



