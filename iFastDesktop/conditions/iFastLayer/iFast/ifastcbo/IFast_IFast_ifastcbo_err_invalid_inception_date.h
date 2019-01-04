#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_inception_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_inception_date() { }
		~CIFast_IFast_ifastcbo_err_invalid_inception_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_INCEPTION_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Inception Date cannot be future dated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date de prise d'effet ne peut être postérieure à la date actuelle.")); }

        // Actions
	};
}



