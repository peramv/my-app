#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_later_monthend_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_later_monthend_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_later_monthend_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LATER_MONTHEND_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date must be 4 weeks from end of current month or a later month end date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum muss 4 Wochen vom Ende des aktuellen Monats liegen oder ein Enddatum eines späteren Monats liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento debe ser 4 semanas antes del fin del mes actual o una fecha de fin de mes posterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance doit différer de 4 semaines de la date de fin du mois en cours ou de l'un des mois suivants.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum moet 4 weken na het einde van de huidige maand of een latere datum aan het einde van de maand zijn")); }

        // Actions
	};
}



