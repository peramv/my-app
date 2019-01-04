#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_next_proc_date_after_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_next_proc_date_after_stop_date() { }
		~CIFast_IFast_ifastcbo_err_warn_next_proc_date_after_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_NEXT_PROC_DATE_AFTER_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Next Process Date after Stop Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nächstes Verarbeitungs-Datum nach Stoppdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de proceso siguiente es posterior a la fecha de baja.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La prochaine date de traitement est postérieure à la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volgende verwerkingsdatum ligt na de einddatum")); }

        // Actions
	};
}



