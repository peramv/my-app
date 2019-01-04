﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_no_delete_object_allowed : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_no_delete_object_allowed() { }
		~CBase_Infrastructure_dicbocore_err_no_delete_object_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_DELETE_OBJECT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. Object %OBJECT% is not deletable.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. Object '^' is not deletable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem. Das Objekt %OBJECT% kann nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. El objeto %OBJECT% no puede eliminarse.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. L'objet %OBJECT% ne peut être supprimé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. Object %OBJECT% kan niet worden gewist")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



