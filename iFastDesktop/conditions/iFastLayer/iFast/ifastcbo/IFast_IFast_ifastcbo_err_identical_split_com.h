#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_identical_split_com : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_identical_split_com() { }
		~CIFast_IFast_ifastcbo_err_identical_split_com() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_IDENTICAL_SPLIT_COM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Split Commissions must differ in Entity Type, Broker Code, Branch Code and Sales Representative Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Geteilte Agenturvergütungen müssen sich unterscheiden in Objekt-Typ, Broker-Code, Filialen-Code und Verkaufsvertreter-Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Las comisiones separadas deben diferir en Tipo de entidad, Código de corredor, Código de sucursal y Código de representante de ventas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les commissions partagées doivent différer en type d'entité, en code de courtier, en code d'unité de service et en code de représentant des ventes.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gedeelde commissies moeten verschillend zijn in eenheidstype, makelaarscode, filiaalcode en vertegenwoordigerscode")); }

        // Actions
	};
}



