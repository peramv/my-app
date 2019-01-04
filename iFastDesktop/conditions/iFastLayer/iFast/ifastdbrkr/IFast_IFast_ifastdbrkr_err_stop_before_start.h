#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_stop_before_start : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_stop_before_start() { }
		~CIFast_IFast_ifastdbrkr_err_stop_before_start() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_STOP_BEFORE_START")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Stop Date is before Start Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Stoppdatum liegt vor dem Startdatum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de baja es anterior a la fecha de inicio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'arrêt est antérieure à la date de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Einddatum ligt voor begindatum")); }

        // Actions
	};
}



