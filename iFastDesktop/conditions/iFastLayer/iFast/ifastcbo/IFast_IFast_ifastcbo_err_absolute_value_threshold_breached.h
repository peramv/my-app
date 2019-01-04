#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_absolute_value_threshold_breached : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_absolute_value_threshold_breached() { }
		~CIFast_IFast_ifastcbo_err_absolute_value_threshold_breached() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ABSOLUTE_VALUE_THRESHOLD_BREACHED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Absolute Value threshold is breached.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le seuil de valeur absolue est dépassé.")); }

        // Actions
	};
}



