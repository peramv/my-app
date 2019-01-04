#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_err_family_name_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_err_family_name_empty() { }
		~CIFast_IFast_ifastbp_err_family_name_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FAMILY_NAME_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Family name empty.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Nom de famille manquant")); }

        // Actions
	};
}



