#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trade_is_part_of_dm_event : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trade_is_part_of_dm_event() { }
		~CIFast_IFast_ifastcbo_err_trade_is_part_of_dm_event() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRADE_IS_PART_OF_DM_EVENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The trade is part of DM event - cannot cancel")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction fait partie d'un événement de gestion de données; impossible de la supprimer.")); }

        // Actions
	};
}



