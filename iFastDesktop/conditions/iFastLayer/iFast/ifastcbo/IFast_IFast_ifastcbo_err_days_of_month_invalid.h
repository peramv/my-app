#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_days_of_month_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_days_of_month_invalid() { }
		~CIFast_IFast_ifastcbo_err_days_of_month_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DAYS_OF_MONTH_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Day of month values must be between 1 and 31.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les valeurs de jour du mois doivent être entre 1 et 31.")); }

        // Actions
	};
}



