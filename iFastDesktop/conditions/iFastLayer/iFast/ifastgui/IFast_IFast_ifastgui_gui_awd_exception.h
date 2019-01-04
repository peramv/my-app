#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_exception : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_exception() { }
		~CIFast_IFast_ifastgui_gui_awd_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD exception thrown; consult an Administrator.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Ausnahme aufgetreten, wenden Sie sich an einen Administrator")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se devolvió una excepción de AWD; consulte a un administrador.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une exception AWD a été renvoyée; consultez un administrateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een AWD-exceptie opgetreden, raadpleeg een beheerder")); }

        // Actions
	};
}



