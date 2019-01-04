#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_seg_event_during_create_trade: public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_seg_event_during_create_trade() { }
		~CIFast_IFast_ifastcbo_err_seg_event_during_create_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEG_EVENT_DURING_CREATE_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A pending seg event exists in the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un évènement de Seg en attente dans le système.")); }

        // Actions
	};
}
