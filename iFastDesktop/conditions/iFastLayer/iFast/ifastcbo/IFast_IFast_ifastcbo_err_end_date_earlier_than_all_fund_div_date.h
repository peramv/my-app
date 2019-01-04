#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_end_date_earlier_than_all_fund_div_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_end_date_earlier_than_all_fund_div_date() { }
		~CIFast_IFast_ifastcbo_err_end_date_earlier_than_all_fund_div_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_END_DATE_EARLIER_THAN_ALL_FUND_DIV_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No account fund has last dividend date earlier than end date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No account fund has last dividend date earlier than end date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun fonds du compte n'a de dernière date de dividende antérieure à la date de fin.")); }

        // Actions
	};
}



