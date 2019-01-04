#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_no_ra_matching_tt : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_no_ra_matching_tt() { }
		~CIFast_IFast_ifastcbo_err_no_ra_matching_tt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RA_MATCHING_TT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Registration Agent with not matching tax type selected.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type d'impôt ne correspond pas à l'agent d'enregistrement sélectionné.")); }

        // Actions
	};
}



