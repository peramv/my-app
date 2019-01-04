#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_ams_err_cannot_purchase_fund_outside_alloc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_ams_err_cannot_purchase_fund_outside_alloc() { }
		~CIFast_IFast_ifastcbo_ams_err_cannot_purchase_fund_outside_alloc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AMS_ERR_CANNOT_PURCHASE_FUND_OUTSIDE_ALLOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot purchase fund outside of AMS fund allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot purchase fund outside of AMS fund allocation.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Cannot purchase fund outside of AMS fund allocation.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'acheter un fonds à l'extérieur de la répartition de fonds de service de gestion de portefeuille.")); }

        // Actions
	};
}



