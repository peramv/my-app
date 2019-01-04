#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_allocation_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_allocation_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_allocation_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ALLOCATION_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Allocation is not allowed for Custom Schedule Trading Fund/Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La répartition n'est pas autorisée pour le fonds/la classe du tableau d'opérations personnalisées.")); }

        // Actions
	};
}



