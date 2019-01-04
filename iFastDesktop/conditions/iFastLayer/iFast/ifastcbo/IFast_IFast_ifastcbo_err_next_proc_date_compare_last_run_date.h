#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_next_proc_date_compare_last_run_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_next_proc_date_compare_last_run_date() { }
		~CIFast_IFast_ifastcbo_err_next_proc_date_compare_last_run_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEXT_PROC_DATE_COMPARE_LAST_RUN_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date results in Next Process Date prior to last run %LAST_RUN_DATE%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei diesem Effektivdatum liegt das Nächster-Verfahren-Datum vor dem Letzter-%LAST_RUN_DATE%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia da como resultado una fecha de siguiente proceso anterior a la última ejecución %LAST_RUN_DATE%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la date du prochain traitement du %LAST_RUN_DATE%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum resulteert in volgende verwerkingsdatum die eerder ligt dan de laatste uitvoering %LAST_RUN_DATE%")); }

        // Actions
	};
}



