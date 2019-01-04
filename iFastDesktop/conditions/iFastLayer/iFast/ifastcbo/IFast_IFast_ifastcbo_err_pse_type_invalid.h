#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pse_type_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pse_type_invalid() { }
		~CIFast_IFast_ifastcbo_err_pse_type_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PSE_TYPE_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid PSE Program Type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Type de programme d'EPS invalide")); }

        // Actions
	};
}



