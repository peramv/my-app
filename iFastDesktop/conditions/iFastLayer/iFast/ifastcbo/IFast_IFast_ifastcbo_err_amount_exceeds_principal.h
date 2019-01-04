#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_exceeds_principal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_exceeds_principal() { }
		~CIFast_IFast_ifastcbo_err_amount_exceeds_principal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_EXCEEDS_PRINCIPAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected amounts exceeds the remaining principal of the investment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les montants sélectionnés excèdent le capital restant de l'investissement.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct.")); }
	};
}



