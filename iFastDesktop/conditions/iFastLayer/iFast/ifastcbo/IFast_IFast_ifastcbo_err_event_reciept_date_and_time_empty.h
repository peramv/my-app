#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_event_reciept_date_and_time_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_event_reciept_date_and_time_empty() { }
		~CIFast_IFast_ifastcbo_err_event_reciept_date_and_time_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EVENT_RECIEPT_DATE_AND_TIME_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Event Receipt Date and Event Receipt Time fields are blank.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Date de réception de l’événement et Heure de réception de l’événement sont vides.")); }

        // Actions
	};
}



