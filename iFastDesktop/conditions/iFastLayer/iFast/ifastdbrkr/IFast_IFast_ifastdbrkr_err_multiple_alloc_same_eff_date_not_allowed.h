#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_multiple_alloc_same_eff_date_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_multiple_alloc_same_eff_date_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_multiple_alloc_same_eff_date_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ALLOC_SAME_EFF_DATE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple active allocations with the same effective date are not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Régler plusieurs répartitions actives avec la même date d'entrée en vigueur n'est pas autorisé")); }

        // Actions
	};
}



