#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_estate_allocation_required_for_death_redemptions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_estate_allocation_required_for_death_redemptions() { }
		~CIFast_IFast_ifastcbo_err_estate_allocation_required_for_death_redemptions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ESTATE_ALLOCATION_REQUIRED_FOR_DEATH_REDEMPTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Estate Allocation is required for Death Redemptions.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Estate Allocation is required for Death Redemptions.")); }

        // Actions
	};
}



