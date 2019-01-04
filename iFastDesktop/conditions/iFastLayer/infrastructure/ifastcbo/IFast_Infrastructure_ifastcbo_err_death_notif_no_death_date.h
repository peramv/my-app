﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_err_death_notif_no_death_date : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_err_death_notif_no_death_date() { }
		~CIFast_Infrastructure_ifastcbo_err_death_notif_no_death_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEATH_NOTIF_NO_DEATH_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Machine is out of memory. There is insufficient disc space.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Machine is out of memory. There is insufficient disc space.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Computer kann nicht mehr speichern. Es gibt nicht genügend Platz auf der Festplatte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La máquina se quedó sin memoria. No hay suficiente espacio en el disco.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La machine n'a plus de mémoire. L'espace sur le disque est insuffisant.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Machine heeft geen geheugen meer. Er is onvoldoende schijfruimte")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



