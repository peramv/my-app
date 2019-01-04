﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_broker_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_broker_not_found() { }
		~CIFast_Infrastructure_ifastdbrkr_err_broker_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_BROKER_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator not authorized for financial institution branch.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator not authorized for financial institution branch.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Operator hat keine Autorisierung für Finanzinstitut-Filiale.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Operador no autorizado para sucursal de institución financiera.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Opérateur non autorisé pour la succursale d'institution financière")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator is niet gemachtigd voor filiaal van financiële instelling")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor, wenn Sie Hilfe zur Operatorsicherheit benötigen.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor for operator security assistance.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour obtenir une assistance en matière de sécurité de l'opérateur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor voor hulp bij operatorveiligheid")); }
	};
}



