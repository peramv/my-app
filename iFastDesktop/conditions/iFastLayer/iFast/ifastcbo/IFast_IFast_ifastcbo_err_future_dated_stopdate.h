#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_future_dated_stopdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_future_dated_stopdate() { }
		~CIFast_IFast_ifastcbo_err_future_dated_stopdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FUTURE_DATED_STOPDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date cannot be future dated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt ne peut être postérieure à la date actuelle.")); }

        // Actions
	};
}



