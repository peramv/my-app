#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_stop_date_fund_same_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_stop_date_fund_same_trade_date() { }
		~CIFast_IFast_ifastdbrkr_err_stop_date_fund_same_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_DATE_FUND_SAME_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date of Fund is prior or same as Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stoppdatum des Fonds liegt vor dem Handelsdatum oder stimmt mit diesem überein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de baja del fondo es anterior o igual a la fecha de transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt du fonds est antérieure ou identique à la date de transaction.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum van fonds ligt eerder of op dezelfde datum als handelsdatum")); }

        // Actions
	};
}



