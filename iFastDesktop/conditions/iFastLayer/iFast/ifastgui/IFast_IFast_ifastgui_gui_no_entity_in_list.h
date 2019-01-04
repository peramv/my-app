#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_no_entity_in_list : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_no_entity_in_list() { }
		~CIFast_IFast_ifastgui_gui_no_entity_in_list() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_ENTITY_IN_LIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("At least one entity must be set up to continue.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Au moins une entite doit être definie pour continuer.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein Objekt muss erstellt werden, um fortfahren zu können.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse al menos una entidad para continuar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous devez régler au moins une entité pour continuer.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet ten minste één eenheid worden ingesteld om door te gaan")); }

        // Actions
	};
}



