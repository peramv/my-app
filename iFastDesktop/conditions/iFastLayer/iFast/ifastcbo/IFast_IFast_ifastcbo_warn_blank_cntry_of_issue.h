#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_blank_cntry_of_issue : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_blank_cntry_of_issue() { }
		~CIFast_IFast_ifastcbo_warn_blank_cntry_of_issue() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_BLANK_CNTRY_OF_ISSUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of issue is blank")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pays d'émission est manquant.")); }

        // Actions
	};
}



