#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_consol_not_valid_for_distribution : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_consol_not_valid_for_distribution() { }
		~CIFast_IFast_ifastcbo_err_consol_not_valid_for_distribution() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONSOL_NOT_VALID_FOR_DISTRIBUTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("\"Netting\" is not available for Distribution")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le net n'est pas disponible pour la distribution.")); }

        // Actions
	};
}



