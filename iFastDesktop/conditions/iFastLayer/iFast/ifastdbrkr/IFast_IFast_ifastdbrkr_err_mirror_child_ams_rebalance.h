#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mirror_child_ams_rebalance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mirror_child_ams_rebalance() { }
		~CIFast_IFast_ifastdbrkr_err_mirror_child_ams_rebalance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIRROR_CHILD_AMS_REBALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot Cancel a Mirror/Child AMS Rebalancing Transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Cannot Cancel a Mirror/Child AMS Rebalancing Transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'annuler une transaction de rebalancement de service de gestion de portefeuille réciproque/jeunesse.")); }

        // Actions
	};
}



