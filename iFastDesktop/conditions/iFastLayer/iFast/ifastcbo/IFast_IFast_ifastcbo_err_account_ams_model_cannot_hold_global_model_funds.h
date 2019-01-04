#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_ams_model_cannot_hold_global_model_funds : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_ams_model_cannot_hold_global_model_funds() { }
		~CIFast_IFast_ifastcbo_err_account_ams_model_cannot_hold_global_model_funds() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_AMS_MODEL_CANNOT_HOLD_GLOBAL_MODEL_FUNDS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account AMS model cannot hold global model fund class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Account AMS model cannot hold global model fund class.")); }

        // Actions
	};
}