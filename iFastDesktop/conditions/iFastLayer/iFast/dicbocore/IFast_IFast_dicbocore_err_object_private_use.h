#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dicbocore_err_object_private_use : public CConditionObject
	{
	public:
		CIFast_IFast_dicbocore_err_object_private_use() { }
		~CIFast_IFast_dicbocore_err_object_private_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_PRIVATE_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Type must be Settle Currency for Investment Allocation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Type must be Settle Currency for Investment Allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Typ muss S sein (Settle Currency=Währung abrechnen) für eine Investment-Zuweisung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo debe ser S (Divisa de liquidación) para Asignación de inversiones.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type doit être Monnaie de règlement pour la répartition d'investissement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Type moet S (Betalingsvaluta) zijn voor beleggingsallocatie")); }

        // Actions
	};
}



