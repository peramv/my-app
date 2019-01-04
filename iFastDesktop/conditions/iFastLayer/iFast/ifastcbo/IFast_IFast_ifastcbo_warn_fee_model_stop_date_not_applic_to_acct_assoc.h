#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_fee_model_stop_date_not_applic_to_acct_assoc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_fee_model_stop_date_not_applic_to_acct_assoc() { }
		~CIFast_IFast_ifastcbo_warn_fee_model_stop_date_not_applic_to_acct_assoc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_FEE_MODEL_STOP_DATE_NOT_APPLIC_TO_ACCT_ASSOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Stop Date change will not be applied to the tree.")); }

        // Actions
	};
}



