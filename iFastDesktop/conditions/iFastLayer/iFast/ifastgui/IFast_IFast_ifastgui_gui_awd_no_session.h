#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_no_session : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_no_session() { }
		~CIFast_IFast_ifastgui_gui_awd_no_session() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_NO_SESSION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD session does not exist.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Sitzung existiert nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La sesión de AWD no existe.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Session AWD inexistante")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-sessie bestaat niet")); }

        // Actions
	};
}



