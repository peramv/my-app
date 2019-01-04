#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_education_inst_post_code_and_country_name_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_education_inst_post_code_and_country_name_required() { }
		~CIFast_IFast_ifastcbo_err_education_inst_post_code_and_country_name_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EDUCATION_INST_POST_CODE_AND_COUNTRY_NAME_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Education Institution Postal Code or Country Name is required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code postal ou le nom du pays de l'établissement d'enseignement est requis.")); }

        // Actions
	};
}



