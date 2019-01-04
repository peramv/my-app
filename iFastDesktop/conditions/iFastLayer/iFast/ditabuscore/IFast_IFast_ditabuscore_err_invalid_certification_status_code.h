#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ditabuscore_err_invalid_certification_status_code : public CConditionObject
	{
	public:
		CIFast_IFast_ditabuscore_err_invalid_certification_status_code() { }
		~CIFast_IFast_ditabuscore_err_invalid_certification_status_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_CERTIFICATION_STATUS_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ditabuscore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A relationship must be selected for this type of entity.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Une relation doit être selectionnee pour ce type d'entite.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine Beziehung muss für diesen Objekttyp gewählt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe seleccionarse una relación para este tipo de entidad.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une relation doit être sélectionnée pour ce type d'entité.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er moet een relatie worden geselecteerd voor dit type eenheid")); }

        // Actions
	};
}



