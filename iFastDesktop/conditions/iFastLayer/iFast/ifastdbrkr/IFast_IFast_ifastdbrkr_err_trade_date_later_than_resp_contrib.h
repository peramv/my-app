#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_date_later_than_resp_contrib : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_date_later_than_resp_contrib() { }
		~CIFast_IFast_ifastdbrkr_err_trade_date_later_than_resp_contrib() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_LATER_THAN_RESP_CONTRIB")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date later than RESP contribution termination date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Handelsdatum liegt nach dem RESP-Einlage-Abschlussdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de transacción es posterior a la fecha de terminación de las aportaciones RESP.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de transaction est postérieure à la date d'échéance de la cotisation REEE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Handelsdatum ligt later dan einddatum RESP-bijdrage")); }

        // Actions
	};
}



