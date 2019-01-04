#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_err_invalid_field_entry : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_err_invalid_field_entry() { }
		~CIFast_IFast_ifastgui_gui_err_invalid_field_entry() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_INVALID_FIELD_ENTRY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid field entry.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entree de zone invalide. Verifiez les informations et ressaisissez.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Feldeintrag. Bestätigen Sie die Information und geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Datos de campo no válidos. Verifique la información y vuelva a introducirlos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Saisie de champ invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige veldinvoer. Controleer de gegevens en voer deze opnieuw in")); }

        // Actions
	};
}



