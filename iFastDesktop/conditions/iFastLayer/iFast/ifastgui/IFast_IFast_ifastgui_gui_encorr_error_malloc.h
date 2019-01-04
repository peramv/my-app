#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_encorr_error_malloc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_encorr_error_malloc() { }
		~CIFast_IFast_ifastgui_gui_encorr_error_malloc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ENCORR_ERROR_MALLOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Encorr memory allocation error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Encorr memory allocation error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Encorr-Speicherzuweisungs-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de asignación de memoria a EnCorr.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'allocation de mémoire Encorr")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij toewijzen Encorr-geheugen")); }

        // Actions
	};
}



