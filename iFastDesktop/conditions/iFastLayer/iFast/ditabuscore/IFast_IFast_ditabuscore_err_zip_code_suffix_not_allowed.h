#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_code_suffix_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_code_suffix_not_allowed() { }
		~CIFast_IFast_ditabuscore_err_zip_code_suffix_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_SUFFIX_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is no value entered for id %ID_VALUE% in entity %ENTITY_ID%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune valeur n'a ete saisie pour l'identification %ID_VALUE% dans l'entite %ENTITY_ID%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es ist kein Wert eingegeben für ID %ID_VALUE% in Objekt %ENTITY_ID%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha introducido un valor para la identificación %ID_VALUE% en la entidad %ENTITY_ID%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune valeur n'a été saisie pour le code %ID_VALUE% de l'entité %ENTITY_ID%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen waarde opgegeven voor ID %ID_VALUE% in eenheid %ENTITY_ID%")); }

        // Actions
	};
}



