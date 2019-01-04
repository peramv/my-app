#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_next_reb_date_cannot_earlier_than_effective_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_next_reb_date_cannot_earlier_than_effective_date() { }
		~CIFast_IFast_ifastcbo_err_next_reb_date_cannot_earlier_than_effective_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEXT_REB_DATE_CANNOT_EARLIER_THAN_EFFECTIVE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Rebalance Date must be after Effective Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Next Rebalance Date must be after Effective Date.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Next Rebalance Date must be after Effective Date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine date de rebalancement doit être postérieure à la date d'entrée en vigueur.")); }

        // Actions
	};
}



