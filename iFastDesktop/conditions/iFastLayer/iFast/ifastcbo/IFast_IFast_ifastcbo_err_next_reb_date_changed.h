#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_next_reb_date_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_next_reb_date_changed() { }
		~CIFast_IFast_ifastcbo_err_next_reb_date_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NEXT_REB_DATE_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Modification of the Next Rebalance Date will cancel the rebalancing schedule for the next cycle run.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Modification of the Next Rebalance Date will cancel the rebalancing schedule for the next cycle run.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Modification of the Next Rebalance Date will cancel the rebalancing schedule for the next cycle run.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une modification de la prochaine date de rebalancement annulera le calendrier de rebalancement pour la prochaine exécution de cycle.")); }

        // Actions
	};
}



