#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_may_less_than_min_init_redemp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_may_less_than_min_init_redemp() { }
		~CIFast_IFast_ifastdbrkr_err_amt_may_less_than_min_init_redemp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_MAY_LESS_THAN_MIN_INIT_REDEMP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount may be less than minimum initial redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag kann unter der minimalen Anfangstilgung liegen:")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto puede ser inferior al rescate inicial mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant peut être inférieur au rachat initial minimal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag kan lager zijn dan minimale eerste aflossing")); }

        // Actions
	};
}



