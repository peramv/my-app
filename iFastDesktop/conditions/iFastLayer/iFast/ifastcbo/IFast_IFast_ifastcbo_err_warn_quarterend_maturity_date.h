#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_quarterend_maturity_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_quarterend_maturity_date() { }
		~CIFast_IFast_ifastcbo_err_warn_quarterend_maturity_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_QUARTEREND_MATURITY_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Maturity date will be set to a quarter end date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fälligkeitsdatum wird auf das Quartalsende gelegt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento se definirá como el último día del trimestre")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance sera réglée à une date de fin de trimestre.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vervaldatum wordt ingesteld op de datum aan het einde van het kwartaal")); }

        // Actions
	};
}



