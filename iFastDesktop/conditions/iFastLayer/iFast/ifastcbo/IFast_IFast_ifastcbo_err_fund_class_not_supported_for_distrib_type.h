#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_class_not_supported_for_distrib_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_class_not_supported_for_distrib_type() { }
		~CIFast_IFast_ifastcbo_err_fund_class_not_supported_for_distrib_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CLASS_NOT_SUPPORTED_FOR_DISTRIB_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and Class are not supported for %DISTRIB_TYPE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe ne sont pas supportés par le type de distribution %DISTRIB_TYPE%.")); }

        // Actions
	};
}



