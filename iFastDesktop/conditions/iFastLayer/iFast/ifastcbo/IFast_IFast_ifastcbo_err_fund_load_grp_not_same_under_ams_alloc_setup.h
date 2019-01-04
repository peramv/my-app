#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fund_load_grp_not_same_under_ams_alloc_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fund_load_grp_not_same_under_ams_alloc_setup() { }
		~CIFast_IFast_ifastcbo_err_fund_load_grp_not_same_under_ams_alloc_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUND_LOAD_GRP_NOT_SAME_UNDER_AMS_ALLOC_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fund Load Group not the same under AMS Allocation Set-up.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le groupe de frais d'acquisition du fonds n'est pas le même que pour le réglage de la répartition de service de gestion de portefeuille.")); }

        // Actions
	};
}



