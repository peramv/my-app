#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_dilution_alloc_resp_date_must_be_between_trade_and_settlement_dates : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_dilution_alloc_resp_date_must_be_between_trade_and_settlement_dates() { }
		~CIFast_IFast_ifastcbo_err_dilution_alloc_resp_date_must_be_between_trade_and_settlement_dates() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DILUTION_ALLOC_RESP_DATE_MUST_BE_BETWEEN_TRADE_AND_SETTLEMENT_DATES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Responsibility Date must be between Trade Date %TRADEDATE% and Current Business Day %SETTLEDATE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de responsabilité doit être entre la date de transactiondu %TRADEDATE% et le jour ouvrable actuel du %SETTLEDATE%.")); }

        // Actions
	};
}



