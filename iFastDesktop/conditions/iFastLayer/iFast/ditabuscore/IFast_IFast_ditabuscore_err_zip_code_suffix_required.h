#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_code_suffix_required : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_code_suffix_required() { }
		~CIFast_IFast_ditabuscore_err_zip_code_suffix_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_SUFFIX_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("For Entity: %ENTITY_ID%, one of the following identification information is required. %IDS%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Identification de l'entite: %ENTITY_ID%. L'une des identifications suivantes est requise: %IDS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Für Objekt: %ENTITY_ID% ist eine der folgenden Identifizierungs-Informationen erforderlich. %IDS%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Para entidad: %ENTITY_ID%, uno de los datos de identificación siguientes es obligatorio. %IDS%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Pour l'entité : %ENTITY_ID%, l'un des renseignements d'identification suivants est requis. %IDS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Voor eenheid: %ENTITY_ID%, is een van de volgende identificatiegegevens vereist. %IDS%")); }

        // Actions
	};
}



