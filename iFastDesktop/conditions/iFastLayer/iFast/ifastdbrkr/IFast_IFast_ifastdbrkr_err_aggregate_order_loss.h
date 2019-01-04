#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_aggregate_order_loss : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_aggregate_order_loss() { }
		~CIFast_IFast_ifastdbrkr_err_aggregate_order_loss() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AGGREGATE_ORDER_LOSS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Aggregate Order is in loss Situation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aggregate Order is in loss Situation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'ordre global est en situation de perte.")); }

        // Actions
	};
}



