﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unknown_sched_user_interface : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unknown_sched_user_interface() { }
		~CIFast_IFast_ifastdbrkr_err_unknown_sched_user_interface() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNKNOWN_SCHED_USER_INTERFACE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unknown scheduler user interface function.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Unbekannte Scheduler-Benutzeroberflächen-Funktion")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Función de interfaz de usuario de programador desconocida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Fonction interface de l'utilisateur programmateur inconnue")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Onbekende functie gebruikersinterface planner")); }

        // Actions
	};
}



