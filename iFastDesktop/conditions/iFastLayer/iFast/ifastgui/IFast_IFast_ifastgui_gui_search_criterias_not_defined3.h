#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_search_criterias_not_defined3 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_search_criterias_not_defined3() { }
		~CIFast_IFast_ifastgui_gui_search_criterias_not_defined3() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_CRITERIAS_NOT_DEFINED3")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Search criteria field is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Suchkriterien werden nicht eingegeben!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los criterios de búsqueda están vacíos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Critère de recherche est vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen zoekcriteria ingevuld!")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please enter the %LABEL1% and/or %LABEL2% and/or %LABEL3%")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie %LABEL1% und/oder %LABEL2% bzw. %LABEL3% ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please enter the %LABEL1% and/or %LABEL2% and/or %LABEL3%")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez entrer l'étiquette %LABEL1%, %LABEL2% ou %LABEL3%.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Geef %LABEL1% en/of %LABEL2% en of %LABEL3% op")); }
	};
}



