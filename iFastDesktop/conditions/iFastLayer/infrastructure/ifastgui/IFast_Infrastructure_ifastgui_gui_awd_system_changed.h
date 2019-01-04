#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_awd_system_changed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_awd_system_changed() { }
		~CIFast_Infrastructure_ifastgui_gui_awd_system_changed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_SYSTEM_CHANGED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Current address is %VALUE% line(s). Name and address cannot exceed %VALUE% lines.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid number of address lines.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktuelle Adresse ist %VALUE% Zeile(n) lang. Name und Adresse können nicht länger als %VALUE% Zeilen sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La dirección actual tiene %VALUE% línea(s). El nombre y la dirección no pueden tener más de  %VALUE% líneas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'adresse actuelle a %VALUE% ligne(s). Le nom et l'adresse ne peuvent excéder %VALUE% lignes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Huidige adres is %VALUE% regel(s). Naam en adres kunnen %VALUE% regels niet overschrijden")); }

        // Actions
	};
}



