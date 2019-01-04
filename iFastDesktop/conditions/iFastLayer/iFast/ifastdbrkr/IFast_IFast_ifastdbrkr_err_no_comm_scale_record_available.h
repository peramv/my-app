#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_comm_scale_record_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_comm_scale_record_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_comm_scale_record_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_COMM_SCALE_RECORD_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Comm-Scale record available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kein Comm-Scale-Eintrag verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay un registro Comm-Scale disponible")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun enregistrement d'échelle de commission disponible")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen records Comm-Scale beschikbaar")); }

        // Actions
	};
}



