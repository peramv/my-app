#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exactly_two_riff_days_of_month_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exactly_two_riff_days_of_month_required() { }
		~CIFast_IFast_ifastcbo_err_exactly_two_riff_days_of_month_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXACTLY_TWO_RIFF_DAYS_OF_MONTH_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exactly two comma separated days of month are required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Exactement deux jours du mois séparés par une virgule sont requis.")); }

        // Actions
	};
}



