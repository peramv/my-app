#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicore_dicore_save_value_fail : public CConditionObject
	{
	public:
		CIFast_IFast_dicore_dicore_save_value_fail() { }
		~CIFast_IFast_dicore_dicore_save_value_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_SAVE_VALUE_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User-access record not found for this user-id.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("User-access record not found for this user-id.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Benutzerzugangs-Eintrag für diese User-ID nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró el registro de acceso del usuario para esta identificación de usuario.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement d'accès utilisateur est introuvable pour ce nom d'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record voor gebruikerstoegang is niet gevonden voor dit gebruikers-ID")); }

        // Actions
	};
}



