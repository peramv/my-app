#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_cannot_greater_than_last_reb_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_cannot_greater_than_last_reb_date() { }
		~CIFast_IFast_ifastcbo_err_date_cannot_greater_than_last_reb_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_CANNOT_GREATER_THAN_LAST_REB_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Date must be before the Last Rebalance Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Date must be before the Last Rebalance Date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Date must be before the Last Rebalance Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date doit être antérieure à la dernière date de rebalancement.")); }

        // Actions
	};
}



