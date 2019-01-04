#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_parent_fund_class_cannot_be_a_part_of_asset_allocation_mix : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_parent_fund_class_cannot_be_a_part_of_asset_allocation_mix() { }
		~CIFast_IFast_ifastcbo_err_parent_fund_class_cannot_be_a_part_of_asset_allocation_mix() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PARENT_FUND_CLASS_CANNOT_BE_A_PART_OF_ASSET_ALLOCATION_MIX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Parent Fund Class cannot be a part of Asset Allocation Mix.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La catégorie Fonds parent ne peut pas faire partie de la répartition d’actifs.")); }

        // Actions
	};
}



