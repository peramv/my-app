﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_language_must_be_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_language_must_be_entered() { }
		~CIFast_IFast_ifastcbo_err_language_must_be_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_LANGUAGE_MUST_BE_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Language field cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone Langue doit être renseignee")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Sprache-Feld darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de idioma no puede estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Langue doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Taalveld mag niet leeg zijn")); }

        // Actions
	};
}



