#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_event_mixing_not_allowed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_event_mixing_not_allowed() { }
		~CIFast_Infrastructure_dicbocore_err_event_mixing_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EVENT_MIXING_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  The current BatchWorkOrder is of type %TYPE%. Other registered events must be of the same event type.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  The current BatchWorkOrder is of type ^. Other registered events must be of the same event type.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Die aktuelle Stapelverarbeitungsanweisung hat den Typ %TYPE%. Andere registrierte Ereignisse müssen den gleichen Ereignistyp haben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  La BatchWorkOrder actual es del tipo %TYPE%. Otros eventos registrados deben ser del mismo tipo de evento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. L'ordre de travail du lot est de type %TYPE%. Les autres événements enregistrés doivent être du même type.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  De huidige BatchWorkOrder is van het type %TYPE%. Andere geregistreerde gebeurtenissen moeten van hetzelfde type gebeurtenis zijn")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



