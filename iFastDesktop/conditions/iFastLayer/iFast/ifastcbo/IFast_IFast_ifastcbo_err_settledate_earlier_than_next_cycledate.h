#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settledate_earlier_than_next_cycledate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settledate_earlier_than_next_cycledate() { }
		~CIFast_IFast_ifastcbo_err_settledate_earlier_than_next_cycledate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEDATE_EARLIER_THAN_NEXT_CYCLEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settle Date earlier than next Cycle Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Abrechnungsdatum liegt vor dem nächsten Zyklusdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de liquidación es anterior a la  fecha del ciclo siguiente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de règlement est antérieure à la prochaine date de cycle.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Betalingsdatum is eerder dan de datum van de volgende cyclus")); }

        // Actions
	};
}



