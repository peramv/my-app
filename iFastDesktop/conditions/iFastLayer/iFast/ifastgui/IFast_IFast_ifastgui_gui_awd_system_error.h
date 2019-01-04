#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_system_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_system_error() { }
		~CIFast_IFast_ifastgui_gui_awd_system_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_SYSTEM_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown System Identification/Management Company.  (%MSG%).")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("%MSG% is an unknown System/Management Company.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%MSG% ist ein unbekanntes System / Management-Unternehmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%MSG% es un sistema o compañía administradora desconocido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Identification de système/d'environnement inconnue (%MSG%)")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%MSG% is een onbekend systeem of beheerbedrijf")); }

        // Actions
	};
}



