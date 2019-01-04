﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_err_awd_profile_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_err_awd_profile_required() { }
		~CIFast_IFast_ifastgui_gui_err_awd_profile_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_AWD_PROFILE_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD is required to complete the current AWD Transaction.  The selected Profile does not support AWD.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD is required to complete the current AWD Transaction.  The selected Profile does not support AWD.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD muss die aktuelle AWD-Transaktion beenden.  Das ausgewählte Profil unterstützt AWD nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere AWD para completar la transacción de AWD actual.  El perfil seleccionado no soporta AWD.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("AWD est requis afin de compléter la transaction courante AWD. Le profil sélectionné ne supporte pas AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD is vereist om de huidige AWD-transactie te voltooien.  Het geselecteerde profiel ondersteunt geen AWD")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Select another Profile")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Select another Profile")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wählen Sie ein anderes Profil")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Select another Profile")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Sélectionnez un autre profil.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Selecteer een ander profiel")); }
	};
}



