#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_notional_amounts_must_be_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_notional_amounts_must_be_negative() { }
		~CIFast_IFast_ifastcbo_warn_notional_amounts_must_be_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NOTIONAL_AMOUNTS_MUST_BE_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Enter amounts with negative sign (-) on redemption and paid out column.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Entrez les montants avec signe négatif (-) sur le rachat et versé colonne.")); }
		
        // Actions
	};
}



