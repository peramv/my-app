#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_biccode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_biccode() { }
		~CIFast_IFast_ifastcbo_err_duplicate_biccode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_BICCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("BIC Code already exists in the system.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code BIC existe déjà dans le système.")); }

        // Actions
	};
}



