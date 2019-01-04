#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_fundbroker_offsettime : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_fundbroker_offsettime() { }
		~CIFast_IFast_ifastcbo_err_invalid_fundbroker_offsettime() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_FUNDBROKER_OFFSETTIME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Offset time must be in range of -1439 to 1439")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'heure de compensation doit être dans la plage entre -1439 et 1439.")); }

        // Actions
	};
}



