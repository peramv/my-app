#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_system_changed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_system_changed() { }
		~CIFast_IFast_ifastgui_gui_awd_system_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_SYSTEM_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The current System/Management Company has changed to %MSG%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Le Systeme/la Societe de gestion courant a ete remplace par %MSG%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das aktuelle System / Management-Unternehmen hat sich geändert in  %MSG%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema/compañía administradora actual ha cambiado por %MSG%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système/l'environnement actuel a changé pour %MSG%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het huidige systeem of beheerbedrijf is gewijzigd in %MSG%")); }

        // Actions
	};
}



