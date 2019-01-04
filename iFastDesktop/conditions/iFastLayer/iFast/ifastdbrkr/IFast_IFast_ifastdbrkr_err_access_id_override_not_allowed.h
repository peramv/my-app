#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_access_id_override_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_access_id_override_not_allowed() { }
		~CIFast_IFast_ifastdbrkr_err_access_id_override_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCESS_ID_OVERRIDE_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Access id override not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Modification de code d'accès non autorisée")); }

        // Actions
	};
}



