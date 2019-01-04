#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deff_until_cannot_be_less_than_today : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deff_until_cannot_be_less_than_today() { }
		~CIFast_IFast_ifastcbo_err_deff_until_cannot_be_less_than_today() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEFF_UNTIL_CANNOT_BE_LESS_THAN_TODAY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date until cannot be less than today.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur ne peut être antérieure à la date actuelle.")); }

        // Actions
	};
}



