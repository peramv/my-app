#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_cannot_be_stopped_before_last_process_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_cannot_be_stopped_before_last_process_date() { }
		~CIFast_IFast_ifastcbo_err_fee_model_cannot_be_stopped_before_last_process_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_CANNOT_BE_STOPPED_BEFORE_LAST_PROCESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee model cannot be stopped before last fee model process date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fee model cannot be stopped before last fee model process date.")); }

        // Actions
	};
}
