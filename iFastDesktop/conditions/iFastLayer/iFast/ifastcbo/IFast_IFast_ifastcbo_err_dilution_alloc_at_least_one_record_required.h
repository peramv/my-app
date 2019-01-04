#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_at_least_one_record_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_at_least_one_record_required() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_at_least_one_record_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_AT_LEAST_ONE_RECORD_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one Dilution Allocation must be setup.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Au moins une répartition de dilution doit être réglée.")); }

        // Actions
	};
}



