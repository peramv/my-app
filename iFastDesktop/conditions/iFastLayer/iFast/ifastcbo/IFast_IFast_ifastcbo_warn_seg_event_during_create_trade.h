#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_seg_event_during_create_trade : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_seg_event_during_create_trade() { }
		~CIFast_IFast_ifastcbo_warn_seg_event_during_create_trade() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SEG_EVENT_DURING_CREATE_TRADE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A pending seg event exists in the system. This financial transaction may not cycle in the correct order. Do you wish to proceed?")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un �v�nement de Seg en attente dans le syst�me. Cette transaction financi�re ne pourrait pas �tre proc�d�e dans le bon ordre. Voulez-vous continuer?")); }

        // Actions
	};
}
