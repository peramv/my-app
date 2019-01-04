#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_zip_code_not_numeric : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_zip_code_not_numeric() { }
		~CIFast_IFast_ditabuscore_err_zip_code_not_numeric() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ZIP_CODE_NOT_NUMERIC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Accountholder entity may only be setup for non-registered tax types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'entite du titulaire de compte (01) ne peut être definie que pour les types de taxes non enregistres.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoinhaber (01)-Objekt kann nur für nicht registrierte Steuertypen erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La entidad de titular de cuenta (01) sólo puede configurarse para tipos tributarios no registrados.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité titulaire du compte ne peut être réglée que pour les types d'imposition non enregistrés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eenheid voor accounthouder (01) kan alleen worden ingesteld voor niet-geregistreerde belastingtypes")); }

        // Actions
	};
}



