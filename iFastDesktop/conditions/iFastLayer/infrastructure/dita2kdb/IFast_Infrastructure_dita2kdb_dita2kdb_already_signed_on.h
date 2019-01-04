#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_already_signed_on : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_already_signed_on() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_already_signed_on() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_ALREADY_SIGNED_ON")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is already signed on.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is already signed on.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Operator ist bereits angemeldet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador ya se ha identificado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'opérateur a déjà une session ouverte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator heeft zich al aangemeld")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify if the operator is signed on to another workstation. If not, contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify if the operator is signed on to another workstation. If not, contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob der Operator an einer anderen Workstation angemeldet ist. Wenden Sie sich andernfalls an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique si el operador está conectado a otra estación de trabajo. Si no lo está, notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez si la session de l'opérateur est ouverte sur un autre poste de travail. Si ce n'est pas le cas, communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of de operator is aangemeld bij een ander werkstation. Neem contact op met een supportmedewerker en meld dit bericht, als dit niet het geval is")); }
	};
}



