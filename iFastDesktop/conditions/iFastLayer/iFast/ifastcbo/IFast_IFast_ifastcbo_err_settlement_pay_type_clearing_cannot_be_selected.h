#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settlement_pay_type_clearing_cannot_be_selected : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settlement_pay_type_clearing_cannot_be_selected() { }
		~CIFast_IFast_ifastcbo_err_settlement_pay_type_clearing_cannot_be_selected() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLEMENT_PAY_TYPE_CLEARING_CANNOT_BE_SELECTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Pay Type Clearing cannot be selected.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Pay Type Clearing cannot be selected.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pay Type Clearing cannot be selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La compensation de type de paiement ne peut être sélectionnée.")); }

        // Actions
	};
}



