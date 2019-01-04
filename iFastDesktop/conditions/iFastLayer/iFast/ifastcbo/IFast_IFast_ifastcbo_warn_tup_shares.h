#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_tup_shares : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_tup_shares() { }
		~CIFast_IFast_ifastcbo_warn_tup_shares() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_TUP_SHARES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Processing of this trade using existing values would result in an estimated final position of %TUPSHARES1% shares.  %TUPSHARES2% shares is calculated by the traded unit position less the estimated units for the inputted trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le traitement de cette transaction par l'utilisation de valeurs existantes résulterait en une position final estimée de %TUPSHARES1% parts. %TUPSHARES2% parts sont calculées par la différence entre la position de l'unité échangée et les unités estimées po")); }

        // Actions
	};
}



