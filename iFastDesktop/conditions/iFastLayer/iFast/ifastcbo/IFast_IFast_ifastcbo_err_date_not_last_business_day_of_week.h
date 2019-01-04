#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_not_last_business_day_of_week : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_not_last_business_day_of_week() { }
		~CIFast_IFast_ifastcbo_err_date_not_last_business_day_of_week() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_NOT_LAST_BUSINESS_DAY_OF_WEEK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Rebalance Date is not the last business day of a week.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Next Rebalance Date is not the last business day of a week.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Next Rebalance Date is not the last business day of a week.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine date de rebalancement ne tombe pas le dernier jour ouvrable d'une semaine.")); }

        // Actions
	};
}



