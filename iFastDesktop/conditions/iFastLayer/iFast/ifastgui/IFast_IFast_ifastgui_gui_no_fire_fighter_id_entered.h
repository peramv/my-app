#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_no_fire_fighter_id_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_no_fire_fighter_id_entered() { }
		~CIFast_IFast_ifastgui_gui_no_fire_fighter_id_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_FIRE_FIGHTER_ID_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No Personal  ID entered.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("No Personal Fire Fighter ID entered.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Personal Fire Fighter ID entered.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun code personnel n'a été saisi.")); }

        // Actions
	};
}



