#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_aggregated_order_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_aggregated_order_not_found() { }
		~CIFast_IFast_ifastbp_bp_err_aggregated_order_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_AGGREGATED_ORDER_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Aggregated order not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aggregated order not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ordre global introuvable")); }

        // Actions
	};
}



