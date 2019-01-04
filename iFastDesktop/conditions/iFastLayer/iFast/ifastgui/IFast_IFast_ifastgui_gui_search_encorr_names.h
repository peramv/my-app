#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_search_encorr_names : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_search_encorr_names() { }
		~CIFast_IFast_ifastgui_gui_search_encorr_names() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_ENCORR_NAMES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Failed to find Encorr Names.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Failed to find Encorr Names.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Encorr-Namen konnten nicht gefunden werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontraron nombres de EnCorr.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de recherche de noms Encorr")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Encorr-namen konden niet worden gevonden")); }

        // Actions
	};
}



