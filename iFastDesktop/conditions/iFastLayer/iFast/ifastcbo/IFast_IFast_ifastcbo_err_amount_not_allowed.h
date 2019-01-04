#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_amount_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount Type is only valid for allocation within the same fund currency.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount Type is only valid for allocation within the same fund currency.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Dollar allocations can only be for the same currency.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de montant n'est valide que pour la répartition dans la même monnaie du fonds.")); }

        // Actions
	};
}



