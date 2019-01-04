#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cycle_calculated_date_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cycle_calculated_date_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_cycle_calculated_date_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CYCLE_CALCULATED_DATE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not allowed for backdated trades.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Non autorisé pour les transaction antidatées")); }

        // Actions
	};
}



