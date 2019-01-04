#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_later_enddate_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_later_enddate_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_later_enddate_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LATER_ENDDATE_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date cannot be later than End date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum darf nicht nach dem Enddatum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento no puede ser posterior a la fecha de terminación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance ne peut être postérieure  à la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum kan niet later zijn dan de einddatum")); }

        // Actions
	};
}



