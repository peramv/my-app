#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_ditabuscore_err_zip_code_suffix_not_allowed : public CConditionObject
	{
	public:
		CBase_Infrastructure_ditabuscore_err_zip_code_suffix_not_allowed() { }
		~CBase_Infrastructure_ditabuscore_err_zip_code_suffix_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_SUFFIX_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip code suffix is not allowed for unformatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip code suffix is not allowed for unformatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Zusatz zur Postleitzahl ist für die unformatierte Adresse nicht zulässig.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permite el sufijo de código postal para las direcciones no formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le suffixe du code postal n'est pas autorisé pour les adresses qui ne sont pas mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Achtervoegsel postcode is niet toegestaan voor niet-ingedeelde adressen")); }

        // Actions
	};
}



