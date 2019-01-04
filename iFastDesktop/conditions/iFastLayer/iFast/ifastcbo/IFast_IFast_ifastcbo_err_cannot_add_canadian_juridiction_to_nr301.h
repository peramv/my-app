#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_add_canadian_juridiction_to_nr301 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_add_canadian_juridiction_to_nr301() { }
		~CIFast_IFast_ifastcbo_err_cannot_add_canadian_juridiction_to_nr301() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_ADD_CANADIAN_JURIDICTION_TO_NR301")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Jurisdiction \"CANADA\" not applicable for NR301.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La juridiction CANADA ne s'applique pas au NR301.")); }

        // Actions
	};
}



