#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_split_factor_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_split_factor_mandatory() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_split_factor_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_SPLIT_FACTOR_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either Allocation Percentage or Responsibility Date is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage de répartition ou la date de responsabilité est requis(e).")); }

        // Actions
	};
}



