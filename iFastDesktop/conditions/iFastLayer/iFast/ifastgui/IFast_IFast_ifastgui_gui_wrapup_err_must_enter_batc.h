#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_batc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_batc() { }
		~CIFast_IFast_ifastgui_gui_wrapup_err_must_enter_batc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_WRAPUP_ERR_MUST_ENTER_BATC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No batch number was entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No batch number was entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es wurde keine Batch-Nummer eingegeben.  Geben Sie eine Batch-Nummer ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo un número de lote. Escriba un número de lote.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun numéro de lot n'a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen batchnummer opgegeven. Typ een batchnummer")); }

        // Actions
	};
}



