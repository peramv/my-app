#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_nodata : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_nodata() { }
		~CIFast_IFast_ifastgui_gui_awd_nodata() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_NODATA")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD Work has no data.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD Work has no data.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Arbeit hat kein Datum.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La tarea de AWD no tiene datos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le travail AWD ne contient aucune donnée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-werk heeft geen gegevens")); }

        // Actions
	};
}



