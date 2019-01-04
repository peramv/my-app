#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_termination_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_termination_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_termination_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TERMINATION_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Termination Date should be 35 years from Inception date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance devrait différer de 35 ans de la date de prise d'effet.")); }

        // Actions
	};
}



