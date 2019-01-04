#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_fields_must_be_unique : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_fields_must_be_unique() { }
		~CIFast_Infrastructure_ifastcbo_err_fields_must_be_unique() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELDS_MUST_BE_UNIQUE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("City name is not allowed for unformatted postal addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("City name is not allowed for unformatted postal addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Name der Stadt ist für die unformatierte Postadresse nicht zulässig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el nombre de la ciudad para las direcciones postales no formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le nom de la ville n'est pas autorisé pour les adresses postales qui ne sont pas mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De plaatsnaam is niet toegestaan voor niet-ingedeelde postadressen")); }

        // Actions
	};
}



