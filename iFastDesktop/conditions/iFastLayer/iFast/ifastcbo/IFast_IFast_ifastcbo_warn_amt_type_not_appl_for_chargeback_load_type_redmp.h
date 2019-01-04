#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_chargeback_load_type_redmp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_chargeback_load_type_redmp() { }
		~CIFast_IFast_ifastcbo_warn_amt_type_not_appl_for_chargeback_load_type_redmp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AMT_TYPE_NOT_APPL_FOR_CHARGEBACK_LOAD_TYPE_REDMP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type %AMT_TYPE% is not applicable for chargeback load redemption.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Amount Type %AMT_TYPE% is not applicable for chargeback load redemption.")); }

        // Actions
	};
}