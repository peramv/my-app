#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_payentity_does_not_exist_for_date_range : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_payentity_does_not_exist_for_date_range() { }
		~CIFast_IFast_ifastdbrkr_err_payentity_does_not_exist_for_date_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAYENTITY_DOES_NOT_EXIST_FOR_DATE_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay entity does not exist for date range.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité de paiement n'existe pas pour la plage de dates.")); }

        // Actions
	};
}



