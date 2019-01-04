#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gic_fund_not_allowed_in_ams : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gic_fund_not_allowed_in_ams() { }
		~CIFast_IFast_ifastcbo_err_gic_fund_not_allowed_in_ams() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GIC_FUND_NOT_ALLOWED_IN_AMS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("GIC funds are not allowed for AMS accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("GIC funds are not allowed for AMS accounts.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("GIC funds are not allowed for AMS accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les fonds CPG ne sont pas autorisés pour les comptes de service de gestion de portefeuille.")); }

        // Actions
	};
}



