#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tup_tolerance_percent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tup_tolerance_percent() { }
		~CIFast_IFast_ifastcbo_warn_tup_tolerance_percent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TUP_TOLERANCE_PERCENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The traded unit position tolerance rate percentage amount is %PERCENT% percent.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant du pourcentage de taux de tolérance de la position de l'unité échangée est de %PERCENT% %.")); }

        // Actions
	};
}



