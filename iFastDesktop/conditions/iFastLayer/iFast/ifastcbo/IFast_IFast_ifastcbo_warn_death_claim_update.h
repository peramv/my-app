#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_death_claim_update : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_death_claim_update() { }
		~CIFast_IFast_ifastcbo_warn_death_claim_update() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DEATH_CLAIM_UPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please update status of Death Claim documents.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez mettre à jour le statut des documents de sinistre-décès.")); }

        // Actions
	};
}



