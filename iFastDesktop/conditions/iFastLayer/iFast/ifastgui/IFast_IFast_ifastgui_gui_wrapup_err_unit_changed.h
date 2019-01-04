#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_wrapup_err_unit_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_wrapup_err_unit_changed() { }
		~CIFast_IFast_ifastgui_gui_wrapup_err_unit_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_WRAPUP_ERR_UNIT_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Business area has changed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Business area has changed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Geschäftsbereich hat sich geändert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El área de negocios ha cambiado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le secteur de marché a changé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrijfsgebied is gewijzigd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie einen neuen Arbeitstyp.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Select a new Work type.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sélectionnez un nouveau type de travail.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Selecteer een nieuw werktype")); }
	};
}



