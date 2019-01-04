#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_less_than_min_init_redemp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_less_than_min_init_redemp() { }
		~CIFast_IFast_ifastdbrkr_err_amt_less_than_min_init_redemp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_LESS_THAN_MIN_INIT_REDEMP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less than minimum initial redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag liegt unter der minimalen Anfangstilgung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto es inferior al rescate inicial mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur au rachat initial minimal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag is lager dan minimale eerste aflossing")); }

        // Actions
	};
}



