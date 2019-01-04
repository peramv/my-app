#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_city_name_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_city_name_required() { }
		~CIFast_Infrastructure_ditabuscore_err_city_name_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CITY_NAME_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("City name is required for formatted postal addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("City name is required for formatted postal addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Name der Stadt ist für die formatierte Postadresse erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el nombre de la ciudad para las direcciones postales formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom de la ville est requis pour les adresses postales mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De plaatsnaam is vereist voor ingedeelde postadressen")); }

        // Actions
	};
}



