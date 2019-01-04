#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cancel_money_out_txns : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cancel_money_out_txns() { }
		~CIFast_IFast_ifastdbrkr_err_cancel_money_out_txns() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANCEL_MONEY_OUT_TXNS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This transaction may affect EUSD tax calculations on the account. Please review and adjust subsequent money out transaction as required")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Subsequent money out trade already exists. Trade cancellation is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette transaction pourrait toucher le calcul de l'EUSD pour le compte. Veuillez réviser et ajuster la transaction de sortie d'argent subséquente tel que demandé.")); }

        // Actions
	};
}



