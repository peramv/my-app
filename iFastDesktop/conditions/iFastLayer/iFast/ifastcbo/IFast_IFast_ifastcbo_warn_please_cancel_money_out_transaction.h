#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_please_cancel_money_out_transaction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_please_cancel_money_out_transaction() { }
		~CIFast_IFast_ifastcbo_warn_please_cancel_money_out_transaction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PLEASE_CANCEL_MONEY_OUT_TRANSACTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This transaction may affect EUSD tax calculations on the account. Please review and adjust subsequent money out transaction as required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Cette transaction pourrait toucher le calcul de l'EUSD pour le compte. Veuillez réviser et ajuster la transaction de sortie d'argent subséquente tel que demandé.")); }

        // Actions
	};
}



