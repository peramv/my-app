#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_scale_detl_record_not_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_scale_detl_record_not_available() { }
		~CIFast_IFast_ifastdbrkr_err_scale_detl_record_not_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SCALE_DETL_RECORD_NOT_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scale-Detl record not available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Scale-Detl-Eintrag nicht verfügbar.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de Scale-Detl no está disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des détails de l'échelle n'est pas disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record Scale-Detl is niet beschikbaar")); }

        // Actions
	};
}



