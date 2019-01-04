#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_if_stop_purch_redem : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_if_stop_purch_redem() { }
		~CIFast_IFast_ifastcbo_err_ams_setup_not_allowed_if_stop_purch_redem() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_SETUP_NOT_ALLOWED_IF_STOP_PURCH_REDEM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AMS setup not allowed if account is stopped for purchases or redemptions.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le réglage du service de gestion de portefeuille n'est pas autorisé si le compte est arrêté pour les achats ou rachats.")); }

        // Actions
	};
}



