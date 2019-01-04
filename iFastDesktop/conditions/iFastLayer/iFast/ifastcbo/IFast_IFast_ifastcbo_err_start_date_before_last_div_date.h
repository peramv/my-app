#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_before_last_div_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_before_last_div_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_before_last_div_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_BEFORE_LAST_DIV_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start Date must be before last Dividend date %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Startdatum muss vor dem letzten Dividendendatum %DATE% liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de inicio debe ser anterior a la última fecha de dividendos %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début doit être antérieure à la dernière date de dividende %DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begindatum moet voor laatste dividenddatum %DATE% liggen")); }

        // Actions
	};
}



