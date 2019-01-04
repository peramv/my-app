#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_allocation_not_support : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_allocation_not_support() { }
		~CIFast_IFast_ifastdbrkr_err_allocation_not_support() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOCATION_NOT_SUPPORT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Allocations are not fully supported for this transaction type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les répartitions des Fonds ne sont pas totalement soutenues pour ce type de transaction.")); }
        // Actions
	};
}



