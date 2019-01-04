#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_stop_adjdate_greater_than_effectivedate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_stop_adjdate_greater_than_effectivedate() { }
		~CIFast_IFast_ifastcbo_err_stop_adjdate_greater_than_effectivedate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_ADJDATE_GREATER_THAN_EFFECTIVEDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop adjustment date must be on or after the account effective date.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt de l'ajustement doit être identique ou postérieure à la date d'entrée en vigueur du compte.")); }

        // Actions
	};
}



