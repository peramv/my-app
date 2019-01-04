#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_cost_allocation_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_cost_allocation_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_at_cost_allocation_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_COST_ALLOCATION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot process an At Cost allocated exchange or transfer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine Zum-Anschaffungswert-zugewiesene Devise oder Transfer kann nicht verarbeitet werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede procesar un traspaso o transferencia asignados al costo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de traiter un échange ou un transfert réparti au coût.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gealloceerde ruil of overdracht tegen kosten kan niet worden verwerkt")); }

        // Actions
	};
}



