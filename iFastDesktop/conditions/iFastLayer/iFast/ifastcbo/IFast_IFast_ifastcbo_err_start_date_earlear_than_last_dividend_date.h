#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_earlear_than_last_dividend_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_earlear_than_last_dividend_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_earlear_than_last_dividend_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_EARLEAR_THAN_LAST_DIVIDEND_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start date cannot be later than last dividend date  %DATE% + 1;")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Start date can not be late than last dividend date  %DATE% + 1;")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Start date can not be late than last dividend date  %DATE% + 1;")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début ne peut être postérieure à la dernière date de dividende %DATE% + 1;")); }

        // Actions
	};
}



