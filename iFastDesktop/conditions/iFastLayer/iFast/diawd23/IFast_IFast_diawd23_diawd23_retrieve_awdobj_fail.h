#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_diawd23_diawd23_retrieve_awdobj_fail : public CConditionObject
	{
	public:
		CIFast_IFast_diawd23_diawd23_retrieve_awdobj_fail() { }
		~CIFast_IFast_diawd23_diawd23_retrieve_awdobj_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_RETRIEVE_AWDOBJ_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The logon request doesn't contain a user id")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Accès refusé: Utilisateur inconnu.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Anmelde-Anfrage enthält keine Benutzer-ID")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud de inicio de sesión no contiene una identificación de usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La demande d'ouverture de session ne contient pas de code d'utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De aanmeldingsaanvraag bevat geen gebruikers-ID")); }

        // Actions
	};
}



