#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_broker_or_branch_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_broker_or_branch_empty() { }
		~CIFast_IFast_ifastbp_bp_err_broker_or_branch_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_BROKER_OR_BRANCH_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Branch code and/or Broker code is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Filialen-Code und/oder Broker-Code sind leer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de sucursal y/o el código de corredor están vacíos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Code d'unité de service ou Code de courtier sont vides.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Filiaalcode en/of makelaarscode is leeg")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please fill in the Branch code and the Broker code")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Tragen Sie den Filialen-Code und den Broker-Code ein")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please fill in the Branch code and the Broker code")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez remplir les champs du code d'unité de service et du code de courtier.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Vul de filiaal- en makelaarscode in")); }
	};
}



