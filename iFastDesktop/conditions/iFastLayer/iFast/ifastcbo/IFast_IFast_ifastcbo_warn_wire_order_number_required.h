#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_wire_order_number_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_wire_order_number_required() { }
		~CIFast_IFast_ifastcbo_warn_wire_order_number_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_WIRE_ORDER_NUMBER_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wire order number is required for wire order trade.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Wire order number is required for wire order trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de l'ordre électronique est requis pour la transaction de l'ordre électronique.")); }

        // Actions
	};
}



