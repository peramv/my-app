#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_avail_units : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_avail_units() { }
		~CIFast_IFast_ifastdbrkr_err_no_avail_units() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_AVAIL_UNITS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No available units.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Anteile verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay unidades disponibles.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune unité disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen beschikbare eenheden")); }

        // Actions
	};
}



