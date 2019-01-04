#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_nightcycle_id_not_found : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_nightcycle_id_not_found() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_nightcycle_id_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_NIGHTCYCLE_ID_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Night Cycle ID not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Night Cycle ID not found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de cycle de nuit introuvable")); }

        // Actions
	};
}



