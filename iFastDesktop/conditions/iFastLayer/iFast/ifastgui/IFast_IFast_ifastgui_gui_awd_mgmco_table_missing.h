#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_mgmco_table_missing : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_mgmco_table_missing() { }
		~CIFast_IFast_ifastgui_gui_awd_mgmco_table_missing() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_MGMCO_TABLE_MISSING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Management Company table is missing.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Management-Unternehmen-Tabelle fehlt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falta la tabla de la compañía administradora.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le tableau de l'environnement est manquant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Tabel beheerbedrijf ontbreekt")); }

        // Actions
	};
}



