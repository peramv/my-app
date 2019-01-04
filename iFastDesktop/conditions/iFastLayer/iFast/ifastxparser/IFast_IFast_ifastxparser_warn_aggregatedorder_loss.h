#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastxparser_warn_aggregatedorder_loss : public CConditionObject
	{
	public:
		CIFast_IFast_ifastxparser_warn_aggregatedorder_loss() { }
		~CIFast_IFast_ifastxparser_warn_aggregatedorder_loss() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_AggregatedOrder_Loss")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastxparser")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("WARN_AggregatedOrder_Loss.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("WARN_AggregatedOrder_Loss.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("WARN_AggregatedOrder_Loss")); }

        // Actions
	};
}



