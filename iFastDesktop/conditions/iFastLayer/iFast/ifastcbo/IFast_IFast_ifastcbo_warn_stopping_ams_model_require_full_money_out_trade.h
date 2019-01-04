#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade() { }
		~CIFast_IFast_ifastcbo_warn_stopping_ams_model_require_full_money_out_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOPPING_AMS_MODEL_REQUIRE_FULL_MONEY_OUT_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("To stop date the AMS model, the user must place a full money-out trade on the AMS model instead.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("To stop date the AMS model, the user must place a full money-out trade on the AMS model instead.")); }

        // Actions
	};
}