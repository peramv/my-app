#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_country_of_exposure_is_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_country_of_exposure_is_required() { }
		~CIFast_IFast_ifastcbo_err_country_of_exposure_is_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_COUNTRY_OF_EXPOSURE_IS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Country of Exposure is required for Politically Exposed Person (PEFP).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Country of Exposure is required for Politically Exposed Person (PEFP).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Country of Exposure is required for Politically Exposed Person (PEFP).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pays d'exposition de l'étranger politiquement vulnérable (EPV) est demandé.")); }

		// Actions
	};
}



