#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_social_code_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_social_code_not_applicable() { }
		~CIFast_IFast_ifastcbo_err_social_code_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SOCIAL_CODE_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This Social Code is not applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code social n'est pas applicable.")); }

        // Actions
	};
}



