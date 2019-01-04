#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_fnd_load_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_fnd_load_type() { }
		~CIFast_IFast_ifastcbo_err_amt_type_not_appl_for_fnd_load_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_TYPE_NOT_APPL_FOR_FND_LOAD_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type %AMT_TYPE% is not applicable for fund load type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Amount Type %AMT_TYPE% is not applicable for fund load type.")); }

        // Actions
	};
}