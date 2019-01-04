#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_data_problem_missing_price : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_data_problem_missing_price() { }
		~CIFast_IFast_ifastdbrkr_err_data_problem_missing_price() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DATA_PROBLEM_MISSING_PRICE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Data problem with missing unit price, please contact technical support.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Data problem with missing unit price, please contact technical support.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Datenproblem mit fehlendem Anteil-Preis, wenden Sie sich bitte an den technischen Support.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Problema de datos con precio de unidad faltante, por favor póngase en contacto con el soporte técnico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème de données en raison d'un prix unitaire manquant. Veuillez communiquer avec le soutien technique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gegevensprobleem met ontbrekende eenheidsprijs, neem contact op met de technische dienst")); }

        // Actions
	};
}



