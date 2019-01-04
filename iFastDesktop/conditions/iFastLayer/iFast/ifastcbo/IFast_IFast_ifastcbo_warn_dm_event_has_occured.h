#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_dm_event_has_occured : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_dm_event_has_occured() { }
		~CIFast_IFast_ifastcbo_warn_dm_event_has_occured() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DM_EVENT_HAS_OCCURED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There has been a DM event since the original trade")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un événement de gestion de données a eu lieu depuis la transaction originale.")); }

        // Actions
	};
}



