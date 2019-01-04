﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_field_not_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_field_not_numeric() { }
		~CIFast_IFast_ditabuscore_err_field_not_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELD_NOT_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Joint type field cannot be blank.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("La zone type joint doit être renseignee.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Feld \"Gemeinschaftstyp\" darf nicht leer sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de tipo de cuenta Conjunta no puede estar en blanco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ Type conjoint doit être rempli.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Veld type Gezamenlijk kan niet leeg zijn")); }

        // Actions
	};
}



