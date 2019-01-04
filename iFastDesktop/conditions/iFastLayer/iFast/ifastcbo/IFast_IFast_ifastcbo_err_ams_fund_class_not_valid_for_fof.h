#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_fund_class_not_valid_for_fof : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_fund_class_not_valid_for_fof() { }
		~CIFast_IFast_ifastcbo_err_ams_fund_class_not_valid_for_fof() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_FUND_CLASS_NOT_VALID_FOR_FOF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund and Class are not defined as Fund of Funds.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds et la classe ne sont pas définis comme fonds de fonds.")); }

        // Actions
	};
}



