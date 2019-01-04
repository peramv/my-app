#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_only_one_split_factor_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_only_one_split_factor_mandatory() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_only_one_split_factor_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_ONLY_ONE_SPLIT_FACTOR_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot enter both Allocation Percentage and Responsibility Date. Only one is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'entrer le pourcentage de répartition et la date de responsabilité. Un seul est requis.")); }

        // Actions
	};
}



