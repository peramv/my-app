#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_exclude_is_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_exclude_is_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_exclude_is_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EXCLUDE_IS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Exclude is not allowed for non-ESG settlement.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'exclusion n'est pas autorisée pour un règlement non ESG.")); }

        // Actions
	};
}



