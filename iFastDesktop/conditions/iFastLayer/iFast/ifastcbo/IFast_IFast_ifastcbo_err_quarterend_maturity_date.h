#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_quarterend_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_quarterend_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_quarterend_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_QUARTEREND_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date must be a quarter end date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum muss ein Datum am Quartalsende sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento debe ser el último día de un trimestre")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance doit être une date de fin de trimestre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum moet een datum aan het eind van het kwartaal zijn")); }

        // Actions
	};
}



