#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_benef_curr_taxyear_mandatory : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_benef_curr_taxyear_mandatory() { }
		~CIFast_IFast_ifastcbo_err_benef_curr_taxyear_mandatory() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BENEF_CURR_TAXYEAR_MANDATORY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Current tax year beneficiary record is mandatory.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement du bénéficiaire pour l'année d'imposition en cours est requis.")); }

        // Actions
	};
}



