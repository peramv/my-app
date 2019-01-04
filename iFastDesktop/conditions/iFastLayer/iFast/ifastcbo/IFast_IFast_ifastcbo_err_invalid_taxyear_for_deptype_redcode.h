#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_taxyear_for_deptype_redcode : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_taxyear_for_deptype_redcode() { }
		~CIFast_IFast_ifastcbo_err_invalid_taxyear_for_deptype_redcode() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TAXYEAR_FOR_DEPTYPE_REDCODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid tax year for %CODE_TYPE% %CODE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Année d'imposition invalide pour %CODE_TYPE% %CODE%")); }

        // Actions
	};
}



