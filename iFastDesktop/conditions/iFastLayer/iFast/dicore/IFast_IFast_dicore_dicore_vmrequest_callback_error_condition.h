#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_vmrequest_callback_error_condition : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_vmrequest_callback_error_condition() { }
		~CIFast_IFast_dicore_dicore_vmrequest_callback_error_condition() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_VMREQUEST_CALLBACK_ERROR_CONDITION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User doesn't have permission to account details screen.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'utilisateur n'est pas autorisé a acceder a l'ecran des details de comptes.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Benutzer ist nicht für das Kontodetail-Fenster zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El usuario no está autorizado a ver la pantalla de detalles de cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'a pas accès à l'écran des détails sur le compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruiker heeft geen toestemming om het scherm met accountdetails te openen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assistance technique.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker")); }
	};
}



