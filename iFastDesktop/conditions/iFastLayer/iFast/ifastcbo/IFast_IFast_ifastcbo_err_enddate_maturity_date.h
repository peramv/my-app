#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_enddate_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_enddate_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_enddate_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ENDDATE_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date must be the same as End date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum muss mit dem Enddatum übereinstimmen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento debe ser igual a la fecha de terminación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance doit être identique à la date de fin.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum moet dezelfde zijn als de einddatum")); }

        // Actions
	};
}



