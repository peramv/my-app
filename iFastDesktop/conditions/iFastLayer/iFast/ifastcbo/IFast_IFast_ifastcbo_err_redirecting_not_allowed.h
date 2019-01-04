#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redirecting_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redirecting_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_redirecting_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDIRECTING_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redirecting to another fund/class is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Réacheminement vers un autre fonds/une autre classe non autorisé")); }

        // Actions
	};
}



