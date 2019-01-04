#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_failed_update_or_create : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_failed_update_or_create() { }
		~CIFast_IFast_ifastgui_gui_awd_failed_update_or_create() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_FAILED_UPDATE_OR_CREATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD failed to update or create AWD Work Object.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein AWD-Arbeitsobjekt konnte nicht durch AWD aktualisiert oder erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("AWD no pudo actualizar o crear el objeto de tarea de AWD.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de la mise à jour AWD ou de la création d'un objet de travail AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het bijwerken of maken van een AWD-werkobject voor AWD is mislukt")); }

        // Actions
	};
}



