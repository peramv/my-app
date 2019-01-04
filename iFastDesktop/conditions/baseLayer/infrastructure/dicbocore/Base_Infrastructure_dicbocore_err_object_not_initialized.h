#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_object_not_initialized : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_object_not_initialized() { }
		~CBase_Infrastructure_dicbocore_err_object_not_initialized() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_OBJECT_NOT_INITIALIZED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. This view is invalid.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. This view is invalid.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das Objekt ist nicht initialisiert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno. Esta view no es válida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Cette vue est invalide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object is niet geïnitialiseerd")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Objekt initialisiert wurde.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of het object is geïnitialiseerd")); }
	};
}



