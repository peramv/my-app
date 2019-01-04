#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unknown_start_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unknown_start_date() { }
		~CIFast_IFast_ifastdbrkr_err_unknown_start_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_START_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown start date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unknown start date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekanntes Startdatum")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fecha de inicio desconocida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Date de début inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende startdatum")); }

        // Actions
	};
}



