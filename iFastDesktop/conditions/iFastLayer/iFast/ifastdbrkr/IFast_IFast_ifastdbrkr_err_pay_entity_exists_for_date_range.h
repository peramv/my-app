#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pay_entity_exists_for_date_range : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pay_entity_exists_for_date_range() { }
		~CIFast_IFast_ifastdbrkr_err_pay_entity_exists_for_date_range() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAY_ENTITY_EXISTS_FOR_DATE_RANGE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay entity exists for date range.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité de paiement existe pour la plage de dates.")); }

        // Actions
	};
}



