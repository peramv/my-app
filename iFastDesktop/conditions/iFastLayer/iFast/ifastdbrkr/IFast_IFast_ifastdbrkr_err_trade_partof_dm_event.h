#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_trade_partof_dm_event : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_trade_partof_dm_event() { }
		~CIFast_IFast_ifastdbrkr_err_trade_partof_dm_event() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_PARTOF_DM_EVENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This trade is part of a DM event - cannot cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("This trade is part of a DM event - cannot cancel.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction s'inscrit dans un événement de gestion de données – impossible de la supprimer.")); }

        // Actions
	};
}



