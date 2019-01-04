#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cntry_of_issue_is_blank : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cntry_of_issue_is_blank() { }
		~CIFast_IFast_ifastcbo_err_cntry_of_issue_is_blank() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CNTRY_OF_ISSUE_IS_BLANK")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of issue is blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Pays d’émission est vide.")); }

        // Actions
	};
}



