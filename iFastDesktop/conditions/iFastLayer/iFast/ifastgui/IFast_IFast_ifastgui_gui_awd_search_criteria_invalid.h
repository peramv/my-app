#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_search_criteria_invalid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_search_criteria_invalid() { }
		~CIFast_IFast_ifastgui_gui_awd_search_criteria_invalid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_SEARCH_CRITERIA_INVALID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search criteria for AWD History is not valid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suchkriterien für AWD-Historie ist ungültig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los criterios de búsqueda para el Historial de AWD no son válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le critère de recherche pour l'historique AWD est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Zoekcriteria voor AWD-historie zijn niet geldig")); }

        // Actions
	};
}



