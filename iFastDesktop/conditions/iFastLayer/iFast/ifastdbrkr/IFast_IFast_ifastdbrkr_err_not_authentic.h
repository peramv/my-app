#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_authentic : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_authentic() { }
		~CIFast_IFast_ifastdbrkr_err_not_authentic() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_AUTHENTIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User cannot be authenticated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur ne peut être authentifié.")); }

        // Actions
	};
}



