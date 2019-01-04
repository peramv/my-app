#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_maxmin_amt_recalculation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_maxmin_amt_recalculation() { }
		~CIFast_IFast_ifastcbo_err_warn_maxmin_amt_recalculation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MAXMIN_AMT_RECALCULATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This transaction will trigger a recalculation of Maximum/Minimum Amounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Diese Transaktion löst eine Neuberechnung der Max/Min-Beträge aus")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Esta transacción generará un recálculo de los montos máximo y mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette transaction va déclencher un recalcul des montants maximal/minimal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deze transactie initieert een nieuwe berekening van max.-/min.-bedragen")); }

        // Actions
	};
}



