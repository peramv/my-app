#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_currencies_not_matching : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_currencies_not_matching() { }
		~CIFast_IFast_ifastcbo_err_fund_currencies_not_matching() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_CURRENCIES_NOT_MATCHING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entered fund currency value (%fund_cur%) does not match the fund level currency (%fund_level_cur%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Entered fund currency value (%fund_cur%) does not match the fund level currency (%fund_level_cur%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de la devise du fonds saisie (%fund_cur%) ne correspond pas à la devise au niveau du fonds (%fund_level_cur%).")); }

        // Actions
	};
}



