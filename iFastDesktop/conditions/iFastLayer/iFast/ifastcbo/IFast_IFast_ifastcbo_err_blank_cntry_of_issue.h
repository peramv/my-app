#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_blank_cntry_of_issue : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_blank_cntry_of_issue() { }
		~CIFast_IFast_ifastcbo_err_blank_cntry_of_issue() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BLANK_CNTRY_OF_ISSUE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("National ID requires country of issue")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code d'identification national requiert un pays d'émission.")); }

        // Actions
	};
}



