#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_e_invalid_sin : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_e_invalid_sin() { }
		~CIFast_IFast_ifastcbo_err_e_invalid_sin() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_E_INVALID_SIN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid social insurance number for %entitydescription%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Invalid social insurance number")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Invalid social insurance number")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("NAS invalide pour %entitydescription%")); }

        // Actions
	};
}



