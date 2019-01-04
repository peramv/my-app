#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_effectivedate_must_be_earlier_stopdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_effectivedate_must_be_earlier_stopdate() { }
		~CIFast_IFast_ifastcbo_err_effectivedate_must_be_earlier_stopdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFFECTIVEDATE_MUST_BE_EARLIER_STOPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date must be earlier than stop date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être antérieure à la date d'arrêt.")); }

        // Actions
	};
}



