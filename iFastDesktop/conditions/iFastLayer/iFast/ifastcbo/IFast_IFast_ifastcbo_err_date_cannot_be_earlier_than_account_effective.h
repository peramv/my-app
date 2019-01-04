#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_date_cannot_be_earlier_than_account_effective : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_date_cannot_be_earlier_than_account_effective() { }
		~CIFast_IFast_ifastcbo_err_date_cannot_be_earlier_than_account_effective() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATE_CANNOT_BE_EARLIER_THAN_ACCOUNT_EFFECTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The field cannot be earlier than account effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ ne peut pas contenir une date antérieure à la date d’effet.")); }

        // Actions
	};
}



