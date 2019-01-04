#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_stopdate_not_valid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_stopdate_not_valid() { }
		~CIFast_IFast_ifastcbo_warn_stopdate_not_valid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_STOPDATE_NOT_VALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date cannot be 12/31/9999.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stop Date cannot be 12/31/9999.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt ne peut être le 31/12/9999.")); }

        // Actions
	};
}



