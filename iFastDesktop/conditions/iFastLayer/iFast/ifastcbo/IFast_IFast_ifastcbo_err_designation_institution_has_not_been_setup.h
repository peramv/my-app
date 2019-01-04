#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_designation_institution_has_not_been_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_designation_institution_has_not_been_setup() { }
		~CIFast_IFast_ifastcbo_err_designation_institution_has_not_been_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DESIGNATION_INSTITUTION_HAS_NOT_BEEN_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Designation Institution has not been setup.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Designation Institution has not been setup.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bezeichnung Institut wurde nicht erstellt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se ha configurado la institución de designación")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'institution de désignation n'a pas été réglée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Aangewezen instelling is niet ingesteld")); }

        // Actions
	};
}



