#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_date_future : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_date_future() { }
		~CIFast_IFast_ifastdbrkr_err_trade_date_future() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_DATE_FUTURE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Trade date future dated.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiges Handelsdatum (liegt in der Zukunft)")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de transacción no válida (futura)")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de la transaction est postérieure à la date actuelle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige handelsdatum (ligt in de toekomst)")); }

        // Actions
	};
}



