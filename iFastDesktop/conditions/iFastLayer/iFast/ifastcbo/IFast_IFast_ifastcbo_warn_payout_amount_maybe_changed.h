#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_payout_amount_maybe_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_payout_amount_maybe_changed() { }
		~CIFast_IFast_ifastcbo_warn_payout_amount_maybe_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAYOUT_AMOUNT_MAYBE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Payout Amount may be changed to %AMOUNT% after cycle processing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Payout Amount may be changed to %AMOUNT% after cycle processing.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Payout Amount may be changed to %AMOUNT% after cycle processing.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de versement pourrait être changé pour %AMOUNT% après le traitement du cycle.")); }

        // Actions
	};
}



