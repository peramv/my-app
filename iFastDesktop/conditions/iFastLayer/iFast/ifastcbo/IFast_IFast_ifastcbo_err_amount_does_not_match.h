#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_does_not_match : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_does_not_match() { }
		~CIFast_IFast_ifastcbo_err_amount_does_not_match() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_DOES_NOT_MATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Difference between ordered amount and fund broker confirmed amount exceeds unit price.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount does not match the aggregated order.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La différence entre le montant demandé et le montant confirmé par le courtier en fonds excède le prix unitaire.")); }

        // Actions
	};
}



