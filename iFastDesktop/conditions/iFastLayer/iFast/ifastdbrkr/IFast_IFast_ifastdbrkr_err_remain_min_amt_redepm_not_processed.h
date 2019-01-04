#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_remain_min_amt_redepm_not_processed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_remain_min_amt_redepm_not_processed() { }
		~CIFast_IFast_ifastdbrkr_err_remain_min_amt_redepm_not_processed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REMAIN_MIN_AMT_REDEPM_NOT_PROCESSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The remaining minimum amount redemption was not processed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die verbleibende Tilgung des Mindestbetrags wurde nicht verarbeitet")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se procesó el rescate del monto mínimo restante")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le rachat du montant minimal restant n'a pas été traité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De resterende aflossing van het minimum bedrag is niet verwerkt")); }

        // Actions
	};
}



