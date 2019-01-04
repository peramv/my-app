#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_distribution_bulking_beneficial : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_distribution_bulking_beneficial() { }
		~CIFast_IFast_ifastcbo_warn_distribution_bulking_beneficial() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_DISTRIBUTION_BULKING_BENEFICIAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There may be benefits to turning on distribution bulking in this account")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il pourrait être avantageux d'activer le regroupement de la distribution pour ce compte.")); }

        // Actions
	};
}



