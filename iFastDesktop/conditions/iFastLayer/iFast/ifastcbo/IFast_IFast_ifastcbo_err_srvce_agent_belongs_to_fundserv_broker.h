#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_srvce_agent_belongs_to_fundserv_broker : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_srvce_agent_belongs_to_fundserv_broker() { }
		~CIFast_IFast_ifastcbo_err_srvce_agent_belongs_to_fundserv_broker() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SRVCE_AGENT_BELONGS_TO_FUNDSERV_BROKER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Service agent belongs to FundSERV broker, please change it via the Commissionable Rep screen.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L’agent du service est un courtier FundSERV. Modifiez-le dans l’écran des représentants à commission.")); }

        // Actions
	};
}



