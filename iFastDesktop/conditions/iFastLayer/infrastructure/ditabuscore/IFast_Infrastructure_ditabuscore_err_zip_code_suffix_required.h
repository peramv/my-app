#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ditabuscore_err_zip_code_suffix_required : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ditabuscore_err_zip_code_suffix_required() { }
		~CIFast_Infrastructure_ditabuscore_err_zip_code_suffix_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_SUFFIX_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Zip code suffix is required for formatted addresses.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Zip code suffix is required for formatted addresses.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Zusatz zur Postleitzahl ist für die formatierte Adresse erforderlich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el sufijo de código postal para las direcciones formateadas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le suffixe du code postal est requis pour les adresses mises en forme.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Achtervoegsel postcode is vereist voor ingedeelde adressen")); }

        // Actions
	};
}



