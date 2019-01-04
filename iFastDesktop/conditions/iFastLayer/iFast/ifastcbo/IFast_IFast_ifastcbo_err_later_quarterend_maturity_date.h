#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_later_quarterend_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_later_quarterend_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_later_quarterend_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LATER_QUARTEREND_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date must be the next or a later quarter end date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum muss am Ende des nächsten oder eines späteren Quartals liegen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento debe ser la siguiente fecha de fin de trimestre o una fecha posterior")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance doit être la prochaine ou l'une des prochaines dates de fin de trimestre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum moet de volgende of een latere datum aan het eind van het kwartaal zijn")); }

        // Actions
	};
}



