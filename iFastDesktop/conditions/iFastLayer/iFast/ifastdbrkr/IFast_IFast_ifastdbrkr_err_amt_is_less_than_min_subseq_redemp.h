#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_amt_is_less_than_min_subseq_redemp : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_amt_is_less_than_min_subseq_redemp() { }
		~CIFast_IFast_ifastdbrkr_err_amt_is_less_than_min_subseq_redemp() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMT_IS_LESS_THAN_MIN_SUBSEQ_REDEMP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less than minimum subsequent redemption.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag liegt unter der minimalen Folgetilgung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto es inferior al rescate posterior mínimo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur au rachat subséquent minimal.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag is lager dan minimale volgende aflossing")); }

        // Actions
	};
}



