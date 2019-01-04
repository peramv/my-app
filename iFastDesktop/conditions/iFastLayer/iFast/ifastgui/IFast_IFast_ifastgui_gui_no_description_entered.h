#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_no_description_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_no_description_entered() { }
		~CIFast_IFast_ifastgui_gui_no_description_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_DESCRIPTION_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Description is mandatory. Please enter it.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La description est requise. Veuillez la saisir.")); }

        // Actions
	};
}



