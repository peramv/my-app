#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_allocamount_less_than_total : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_allocamount_less_than_total() { }
		~CIFast_IFast_ifastcbo_err_allocamount_less_than_total() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOCAMOUNT_LESS_THAN_TOTAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The allocation amount can not be less than the total amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de répartition ne peut être inférieur au montant total.")); }

        // Actions
	};
}



