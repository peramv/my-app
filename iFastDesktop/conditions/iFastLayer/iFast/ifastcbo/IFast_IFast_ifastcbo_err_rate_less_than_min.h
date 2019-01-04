#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rate_less_than_min : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rate_less_than_min() { }
		~CIFast_IFast_ifastcbo_err_rate_less_than_min() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RATE_LESS_THAN_MIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rate should not be less than minimum %MINRATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rate should not be less than minimum %MINRATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Rate should not be less than minimum %MINRATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le taux ne devrait pas être inférieur au minimum : %MINRATE%.")); }

        // Actions
	};
}



