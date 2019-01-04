#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_non_business_day_for_deal_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_non_business_day_for_deal_date() { }
		~CIFast_IFast_ifastcbo_err_non_business_day_for_deal_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NON_BUSINESS_DAY_FOR_DEAL_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Non-business day for deal date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Geschäftstag für Abschlussdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Día no hábil para fecha de transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de l'opération n'est pas un jour ouvrable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen werkdag voor handelsdatum")); }

        // Actions
	};
}



