#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_guard_option : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_guard_option() { }
		~CIFast_IFast_ifastcbo_err_invalid_guard_option() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_GUARD_OPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid Guard Option. Please re-enter.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Option de garde invalide. Veuillez réessayer.")); }

        // Actions
	};
}



