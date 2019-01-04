#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_at_fundto_classto_acountto_same_as_from : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_at_fundto_classto_acountto_same_as_from() { }
		~CIFast_IFast_ifastcbo_err_at_fundto_classto_acountto_same_as_from() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AT_FUNDTO_CLASSTO_ACOUNTTO_SAME_AS_FROM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Automatic Transfer to same Fund Code, Fund Class and same Account is not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Automatic Transfer to same Fund Code, Fund Class and same Account is not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Automatischer Transfer zum gleichen Fondscode, zur gleichen Fondsklasse und zum selben Konto ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten trasferencias automáticas al mismo código de fondo, clase de fondo y a la misma cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert automatique au même code de fonds, à la même classe de fonds et au même compte n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Automatische overdracht naar dezelfde fondscode, fondscategorie en hetzelfde account is niet toegestaan")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("please  re-enter")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("please  re-enter")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Bitte geben Sie neu ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("please  re-enter")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez recommencer la saisie.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("vul opnieuw in")); }
	};
}



