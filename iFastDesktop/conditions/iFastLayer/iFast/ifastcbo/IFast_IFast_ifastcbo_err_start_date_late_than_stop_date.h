#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_late_than_stop_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_late_than_stop_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_late_than_stop_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_LATE_THAN_STOP_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Start date must precede End date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Startdatum muss vor dem Enddatum liegen Bitte geben Sie das Enddatum neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de inicio debe preceder a la fecha de baja. Por favor vuelva a introducir la fecha de baja.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de début doit être antérieure à la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Begindatum moet voor einddatum liggen. Vul de einddatum opnieuw in")); }

        // Actions
	};
}



