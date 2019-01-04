#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_agent_warn_purchase_sls_rep_lvl_not_met : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_agent_warn_purchase_sls_rep_lvl_not_met() { }
		~CIFast_IFast_ifastcbo_agent_warn_purchase_sls_rep_lvl_not_met() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("AGENT_WARN_PURCHASE_SLS_REP_LVL_NOT_MET")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Sales representative level does not allow for purchase with borrowed money.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sales representative level does not allow for purchase with borrowed money.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sales representative level does not allow for purchase with borrowed money.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le niveau du représentant des ventes n'autorise pas un achat avec de l'argent emprunté.")); }

        // Actions
	};
}



