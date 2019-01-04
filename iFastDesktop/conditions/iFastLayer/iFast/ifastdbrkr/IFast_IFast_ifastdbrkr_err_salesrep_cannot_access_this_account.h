﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_salesrep_cannot_access_this_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_salesrep_cannot_access_this_account() { }
		~CIFast_IFast_ifastdbrkr_err_salesrep_cannot_access_this_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SALESREP_CANNOT_ACCESS_THIS_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("User does not have access to either broker/branch/sales representative or shareholder group.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("L'acces a ce compte est interdit au responsables")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Verkaufsvertreter darf nicht auf dieses Konto zugreifen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El representante de ventas no puede acceder a esta cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'utilisateur n'a pas accès au courtier/à l'unité de service/au représentant des ventes ou au groupe d'actionnaires.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vertegenwoordiger kan dit account niet openen")); }

        // Actions
	};
}



