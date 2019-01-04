#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_death_settlement_stamped : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_death_settlement_stamped() { }
		~CIFast_IFast_ifastcbo_warn_death_settlement_stamped() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEATH_SETTLEMENT_STAMPED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Death Settlement Date was stamped.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de règlement de succession a été marquée.")); }

        // Actions
	};
}



