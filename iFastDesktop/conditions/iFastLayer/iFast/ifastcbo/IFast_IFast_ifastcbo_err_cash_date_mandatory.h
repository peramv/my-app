#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cash_date_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cash_date_mandatory() { }
		~CIFast_IFast_ifastcbo_err_cash_date_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CASH_DATE_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cash Date is mandatory for Backdated Trades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cash Date is mandatory for Backdated Trades.")); }

        // Actions
	};
}



