#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_current_date_subscribed_units_included : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_current_date_subscribed_units_included() { }
		~CIFast_IFast_ifastcbo_warn_current_date_subscribed_units_included() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CURRENT_DATE_SUBSCRIBED_UNITS_INCLUDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Money out transaction includes units subscribed on the current trade date for %FUND%/%CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction de sortie de fonds comprend des unités souscrites en date du jour pour %FUND%/%CLASS%.")); }

        // Actions
	};
}



