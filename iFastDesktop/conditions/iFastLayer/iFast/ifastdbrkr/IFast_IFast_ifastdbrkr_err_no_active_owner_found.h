#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_active_owner_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_active_owner_found() { }
		~CIFast_IFast_ifastdbrkr_err_no_active_owner_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACTIVE_OWNER_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No active owner is found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun titulaire actif trouvé")); }

        // Actions
	};
}



