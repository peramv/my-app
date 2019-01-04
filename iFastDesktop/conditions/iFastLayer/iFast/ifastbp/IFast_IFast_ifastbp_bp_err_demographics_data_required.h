#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_demographics_data_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_demographics_data_required() { }
		~CIFast_IFast_ifastbp_bp_err_demographics_data_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_DEMOGRAPHICS_DATA_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Demographics data required.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Données sociodémographiques requises")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please enter demographics data before continue.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez saisir les données sociodémographiques avant de continuer.")); }
	};
}



