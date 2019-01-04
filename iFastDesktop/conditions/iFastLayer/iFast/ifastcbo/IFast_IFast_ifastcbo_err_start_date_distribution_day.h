#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_distribution_day : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_distribution_day() { }
		~CIFast_IFast_ifastcbo_err_start_date_distribution_day() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_DISTRIBUTION_DAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start date must be last distribtion date %DATE% +1;")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Start date must be last distribtion date %DATE% +1;")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Start date must be last distribtion date %DATE% +1;")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début doit être identique à la dernière date de distribution %DATE% + 1;")); }

        // Actions
	};
}



