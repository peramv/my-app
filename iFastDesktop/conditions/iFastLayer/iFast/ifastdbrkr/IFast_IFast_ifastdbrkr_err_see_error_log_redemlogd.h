#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_see_error_log_redemlogd : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_see_error_log_redemlogd() { }
		~CIFast_IFast_ifastdbrkr_err_see_error_log_redemlogd() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SEE_ERROR_LOG_REDEMLOGD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please see error log 'REDEMLOG.D'.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bitte sehen Sie das Fehlerprotokoll REDEMLOG.D ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Por favor vea el registro de error ‘REDEMLOG.D’.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez consulter la note d'erreur REDEMLOG.D.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Raadpleeg het foutenlogboek ?REDEMLOG.D?")); }

        // Actions
	};
}



