﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_trade_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid trade date. Next valid trade date is %TRADEDATE%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Date d'operation invalide. La date d'operation valide suivante est %TRADEDATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Handelsdatum. Nächstes gültiges Handelsdatum ist %TRADEDATE%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de transacción no válida. La siguiente fecha de transacción válida es %TRADEDATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de transaction invalide. La prochaine date de transaction valide est le %TRADEDATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige handelsdatum. Volgende geldige handelsdatum is %TRADEDATE%")); }

        // Actions
	};
}



