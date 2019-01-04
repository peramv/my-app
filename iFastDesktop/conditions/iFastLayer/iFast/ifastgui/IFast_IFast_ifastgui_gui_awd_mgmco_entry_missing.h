#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_mgmco_entry_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_mgmco_entry_missing() { }
		~CIFast_IFast_ifastgui_gui_awd_mgmco_entry_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_MGMCO_ENTRY_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Entry missing from Management Company table.  (%LABEL1%).  Contact AWD Support.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag in der Management-Unternehmen-Tabelle fehlt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta una entrada en la tabla de la compañía administradora.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisie manquante dans la table de l'environnement. (%LABEL1%). Communiquez avec le soutien AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er ontbreekt een gegeven in de tabel beheerbedrijf")); }

        // Actions
	};
}



