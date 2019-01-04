#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_not_within_reinvest_purchase_schedule : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_not_within_reinvest_purchase_schedule() { }
		~CIFast_IFast_ifastcbo_err_fund_not_within_reinvest_purchase_schedule() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_NOT_WITHIN_REINVEST_PURCHASE_SCHEDULE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund %FUND% is not within reinvestment purchase schedule for trade date %DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fund %FUND% is not within reinvestment purchase schedule for trade date %DATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds %FUND% n'est pas dans le calendrier d'achat de réinvestissement pour la date de transaction du %DATE%.")); }

        // Actions
	};
}



