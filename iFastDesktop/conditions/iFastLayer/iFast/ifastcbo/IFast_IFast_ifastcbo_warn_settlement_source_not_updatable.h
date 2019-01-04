#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settlement_source_not_updatable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settlement_source_not_updatable() { }
		~CIFast_IFast_ifastcbo_warn_settlement_source_not_updatable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_SETTLEMENT_SOURCE_NOT_UPDATABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement source is not updatable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La source de règlement ne peut être mise à jour.")); }

        // Actions
	};
}



