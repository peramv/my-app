#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_broker_or_branch_or_slsrep_empty : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_broker_or_branch_or_slsrep_empty() { }
		~CIFast_IFast_ifastbp_bp_err_broker_or_branch_or_slsrep_empty() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_BROKER_OR_BRANCH_OR_SLSREP_EMPTY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Branch code, Broker code and/or Sales Representative code is empty.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Filialen-Code, Broker-Code und/oder Verkaufsvertreter-Code ist/sind leer")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El código de sucursal, el código de corredor y/o el código de representante de ventas están vacíos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les champs Code d'unité de service, Code de courtier ou Code de représentant des ventes sont vides.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Filiaalcode, makelaarscode en/of vertegenwoordigerscode is leeg")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please fill Branch code, Broker code  and Sales Representative code")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Tragen Sie den Filialen-Code, den Broker-Code und den Verkaufsvertreter-Code ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please fill Branch code, Broker code  and Sales Representative code")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez remplir les champs du code d'unité de service, du code de courtier et du code de représentant des ventes.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Vul de filiaalcode, de makelaarscode en de vertegenwoordigerscode in")); }
	};
}



