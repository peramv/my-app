#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settledate_earlier_than_tradedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settledate_earlier_than_tradedate() { }
		~CIFast_IFast_ifastcbo_err_settledate_earlier_than_tradedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEDATE_EARLIER_THAN_TRADEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle Date earlier than Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abrechnungsdatum liegt vor dem Handelsdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de liquidación es anterior a la  fecha de transacción")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de règlement est antérieure à la date de transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsdatum is eerder dan de handelsdatum")); }

        // Actions
	};
}



