#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_wrkt : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_wrkt() { }
		~CIFast_Infrastructure_ifastgui_gui_wrapup_err_must_enter_wrkt() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_WRAPUP_ERR_MUST_ENTER_WRKT")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("SYSTRAN instructions exist.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("SYSTRAN instructions exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("SYSTRAN-Anweisungen existieren.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Existen instrucciones SYSTRAN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Instructions SYSTRAN existantes")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er bestaan SYSTRAN-instructies")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Kontooptionen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Review account options.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Passez en revue les options du compte.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Herzie de accountmogelijkheden")); }
	};
}



