#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_invalid_mapped_event : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_invalid_mapped_event() { }
		~CIFast_IFast_ifastgui_gui_awd_invalid_mapped_event() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_INVALID_MAPPED_EVENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid value; improperly mapped AWD Worktype Event.  (%LABEL1%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Wert, falsch gemapptes AWD-Worktype-Ereignis.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Valor no aceptado; evento de tipo de tarea de AWD incorrectamente mapeado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Valeur invalide; l'événement du type de travail AWD n'a pas été convenablement appliqué. (%LABEL1%).")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige waarde; onjuist toegewezen gebeurtenis AWD-werktype")); }

        // Actions
	};
}



